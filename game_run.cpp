#include <SDL.h>
#include <cstdio>
#include <fstream>
#include <vector>
#include <cassert>
#include <cstring>
#include <queue>
#include "constant.h"
#include "definition.h"
#include "game_run.h"
#include "tiles.h"

const int dx[2][2] = {{0, 0}, {-1, 1}},       // Use for
    dy[2][2] = {{-1, 1}, {0, 0}};             // BFS Search
int par[MAX_ROWS + 2][MAX_COLUMNS + 2][2][3]; // for BFS Search and trace
// we compress 4 identify index into 1 int-type variable 
// row * 2^24 + cols * 2 ^ 16 + dir * 2^3 + number_of_change * 2^0

int numCols, numRows, numRemains;
SDL_Rect table;
cellStatus cell[MAX_ROWS][MAX_COLUMNS]; // status of cells in table
cellStatus cellBackButton;
std::vector<traceSegment> segments;

int numChosen;
SDL_Point posChosen[2];

SDL_Texture *last_match; // The mahjong tile that player has just match
SDL_Rect last_match_pos; // Where to display

std::string level;
int score;    
bool playedMusic = false;

extern type_Screen currentScreen; // type_Screen

void gameRender(SDL_Renderer *gRenderer)
{
    if (numRemains == 0) // Player won game
    {
        // for(int i = 0; i * TILE_WIDTH < SCREEN_WIDTH; ++i)
        // for(int j = 0; j * TILE_HEIGHT < SCREEN_HEIGHT; ++j)
        //     if((i & 1) == (j & 1)) {
        //         SDL_Rect tempRect = {i * TILE_WIDTH, j * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT};
        //         SDL_RenderCopy(gRenderer, chosen_Highlight, NULL, &tempRect);
        //     }
        if (!playedMusic)
        {
            Mix_PauseMusic();
            Mix_PlayChannel(-1, winMusic, 0);
            // Mix_ResumeMusic();
            playedMusic = true;
        }

        SDL_Rect dstRect = {(SCREEN_WIDTH - win_Screen.w) / 2, (SCREEN_HEIGHT - win_Screen.h) / 2, win_Screen.w, win_Screen.h};
        SDL_RenderCopy(gRenderer, win_Screen.getTexture(), NULL, &dstRect);
    }
    else
    {
        SDL_RenderCopy(gRenderer, cellBackButton.getTexture(), NULL, &cellBackButton.dstRect); // for back button
        SDL_RenderCopy(gRenderer, last_match, NULL, &last_match_pos);

        for (int i = 0; i < numRows; ++i)
            for (int j = 0; j < numCols; ++j)
                if (!cell[i][j].empty())
                {

                    assert(cell[i][j].tile != NULL);
                    SDL_RenderCopy(gRenderer, cell[i][j].getTexture(), NULL, &cell[i][j].dstRect);

                    if (cell[i][j].getCheckChosen())
                        SDL_RenderCopy(gRenderer, chosen_Highlight, NULL, &cell[i][j].dstRect);
                }
                else
                    SDL_RenderCopy(gRenderer, chosen_Highlight, NULL, &cell[i][j].dstRect);
        
        SDL_SetRenderDrawColor(gRenderer, 0, 204, 0, 200);
        for(int i = (int)segments.size() - 1; ~i; --i) // Draw segments
        {
            segments[i].Draw(gRenderer);

            if(segments[i].Exist() == 0) // Out of time 
            {
               segments[i] = segments.back();
               segments.pop_back();
            }
        }
    }
}

void createBackButton()
{
    table = {(SCREEN_WIDTH - 20 * CELL_WIDTH) / 2, (SCREEN_HEIGHT - 11 * CELL_HEIGHT) / 2, 20 * CELL_WIDTH, 11 * CELL_HEIGHT};

    SDL_Rect dstRect = {(table.x - BUTTON_WIDTH * 80 / 100) / 2, (table.y + CELL_HEIGHT - BUTTON_HEIGHT * 80 / 100) / 2, BUTTON_WIDTH * 80 / 100, BUTTON_HEIGHT * 80 / 100};
    cellBackButton.set(&backButton, dstRect);
}

void processGameMouseDown(int x, int y)
{
    if (Inside(cellBackButton.dstRect, {x, y}))
    {
        currentScreen = MENU_SCREEN;
        return;
    }

    for (int i = 0; i < numRows; ++i)
        for (int j = 0; j < numCols; ++j)
            if (cell[i][j].canClick() && Inside(cell[i][j].dstRect, {x, y}))
            {

                if (cell[i][j].click())
                {
                    posChosen[numChosen++] = {i, j};
                }
                else
                {
                    assert(numChosen == 1);
                    --numChosen;
                }

                goto done;
            }
done:;

    if (numChosen == 2)
    {
        if (cell[posChosen[0].x][posChosen[0].y].tile == cell[posChosen[1].x][posChosen[1].y].tile && canReach(posChosen[0], posChosen[1]))
        {
            cell[posChosen[0].x][posChosen[0].y].disAppear();
            cell[posChosen[1].x][posChosen[1].y].disAppear();

            numRemains -= 2;
            last_match = cell[posChosen[0].x][posChosen[0].y].getTexture();

            //Trace for draw segments

            for(int dir = 0; dir < 2; ++dir)
                for(int num_change = 0; num_change < 3; ++num_change) 
                    if(par[posChosen[1].x + 1][posChosen[1].y + 1][dir][num_change] != -1) // this state, but we need to add 1 to coordinator of poschosen
                    {
                        Trace(posChosen[0], posChosen[1], dir, num_change);
                        goto done_trace;
                    }
            done_trace:;
        }

        cell[posChosen[0].x][posChosen[0].y].click();
        cell[posChosen[1].x][posChosen[1].y].click();
        numChosen = 0;
    }
}

SDL_Point getCenter(SDL_Point coordinate) {
    if(Inside(table, coordinate)) 
        return Center(cell[coordinate.x - 1][coordinate.y - 1].dstRect);

    SDL_Rect dst;
    dst.x = coordinate.y < 1 ? table.x - CELL_WIDTH : (coordinate.y > numCols ? table.x + table.w : (coordinate.y - 1) * CELL_WIDTH + table.x);
    dst.y = coordinate.x < 1 ? table.y - CELL_HEIGHT : (coordinate.x > numRows ? table.y + table.h : (coordinate.x - 1) * CELL_HEIGHT + table.y);
    dst.w = CELL_WIDTH;
    dst.h = CELL_HEIGHT;

    return Center(dst);
}

void Trace(SDL_Point src, SDL_Point dst, int dir, int num_change) {
    ++src.x;
    ++src.y;
    ++dst.x;
    ++dst.y; // Add coordinator by 1

    for (SDL_Point roller = dst; roller.x != src.x || roller.y != src.y;) {
        
        SDL_Point temp = {  (par[roller.x][roller.y][dir][num_change] >> 24) & 255,
                            (par[roller.x][roller.y][dir][num_change] >> 16) & 255};
        
        //getCenter(roller), getCenter(temp);
        segments.emplace_back(getCenter(roller), getCenter(temp), SEGMENT_COUNT_EXIST);

        dst = { (par[roller.x][roller.y][dir][num_change] >> 8) & 255,
                    par[roller.x][roller.y][dir][num_change] & 255 };
        dir = dst.x;
        num_change = dst.y;

        roller = temp;
    }
}

bool canReach(SDL_Point src, SDL_Point dst)
{
    memset(par, -1, sizeof par);
    ++src.x;
    ++src.y;
    ++dst.x;
    ++dst.y; // Add coordinator by 1

    struct Tque
    {
        int x, y, dir, num_change;
        Tque(int x = 0, int y = 0, int dir = 0, int num_change = 0) : x(x), y(y), dir(dir), num_change(num_change) {}
    };
    std::queue<Tque> q;

    par[src.x][src.y][0][0] = par[src.x][src.y][1][0] = 0;
    q.emplace(src.x, src.y, 0, 0);
    q.emplace(src.x, src.y, 1, 0);

    while (!q.empty())
    {
        Tque c = q.front();
        q.pop();

        if (c.x == dst.x && c.y == dst.y)
            return true;

        for (int i = 0; i < 2; ++i)
        {
            // same dir
            {
                int u = c.x + dx[c.dir][i],
                    v = c.y + dy[c.dir][i];

                if (u >= 0 && u <= numRows + 1 && v >= 0 && v <= numCols + 1 && (u == 0 || u == numRows + 1 || v == 0 || v == numCols + 1 || !cell[u - 1][v - 1].isAppear || (u == dst.x && v == dst.y)))
                {
                    if (par[u][v][c.dir][c.num_change] == -1)
                    {
                        par[u][v][c.dir][c.num_change] = (c.x << 24) + (c.y << 16) + (c.dir << 8) + (c.num_change << 0);
                        q.emplace(u, v, c.dir, c.num_change);
                    }
                }
            }

            // different dir
            if (c.num_change < 2)
            {
                int u = c.x + dx[c.dir ^ 1][i],
                    v = c.y + dy[c.dir ^ 1][i];

                if (u >= 0 && u <= numRows + 1 && v >= 0 && v <= numCols + 1 && (u == 0 || u == numRows + 1 || v == 0 || v == numCols + 1 || !cell[u - 1][v - 1].isAppear || (u == dst.x && v == dst.y)))
                {
                    if (par[u][v][c.dir ^ 1][c.num_change + 1] == -1)
                    {
                        par[u][v][c.dir ^ 1][c.num_change + 1] = (c.x << 24) + (c.y << 16) + (c.dir << 8) + (c.num_change << 0);
                        q.emplace(u, v, c.dir ^ 1, c.num_change + 1);
                    }
                }
            }
        }
    }

    return false; // can't reach
}

void assignLevel(const std::string &lv)
{
    level = lv; // assign level
    score = 0; // reset score
    std::ifstream inf(("levels\\" + level + ".txt").c_str());

    inf >> numRows >> numCols;

    table = {(SCREEN_WIDTH - 20 * CELL_WIDTH) / 2, (SCREEN_HEIGHT - 11 * CELL_HEIGHT) / 2, 20 * CELL_WIDTH, 11 * CELL_HEIGHT};

    last_match = chosen_Highlight;
    last_match_pos = {(table.x - TILE_WIDTH) / 2, (table.y + table.h - TILE_HEIGHT) / 2, TILE_WIDTH, TILE_HEIGHT};

    numRemains = numRows * numCols;
    std::vector<int> id(numRows * numCols / 2);
    for (auto &i : id)
        i = rand(0, MAX_NUM_TILES - 1);

    for (int i = 0; i < numRows; ++i)
        for (int j = 0; j < numCols; ++j)
        {
            int x;
            inf >> x;

            SDL_Rect dstRect = {j * CELL_WIDTH + table.x, i * CELL_HEIGHT + table.y, TILE_WIDTH, TILE_HEIGHT};
            setCell(i, j, &tile[id[x]], dstRect);
        }

    id.clear();
    id.shrink_to_fit();
    numChosen = 0; // For new game
    inf.close();
}

void resetCell(int x, int y)
{
    cell[x][y].reset();
}

void setCell(int x, int y, textureObject *tile, SDL_Rect dstRect)
{
    cell[x][y].set(tile, dstRect);
}