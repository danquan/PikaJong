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
#include "textures.h"

const int dx[2][2] = {{0, 0}, {-1, 1}},       // Use for
    dy[2][2] = {{-1, 1}, {0, 0}};             // BFS Search
int par[MAX_ROWS + 2][MAX_COLUMNS + 2][2][3]; // for BFS Search and trace
// we compress 4 identify index into 1 int-type variable 
// row * 2^24 + cols * 2 ^ 16 + dir * 2^3 + number_of_change * 2^0

int numCols, numRows, numRemains;
SDL_Rect table; // where to show tiles
cellStatus cell[MAX_ROWS][MAX_COLUMNS]; // status of cells in table
bool isDisappear[MAX_ROWS][MAX_COLUMNS]; // use if tile has been deleted
bool isChosen[MAX_ROWS][MAX_COLUMNS]; // use if tle has been chosen

cellStatus cellBackButton, winScreen;
std::vector<traceSegment> segments;

int numChosen;
SDL_Point posChosen[2];

std::string level;
int score;

extern type_Screen currentScreen; // type_Screen

void gameRender(SDL_Renderer *gRenderer)
{
    if (numRemains == 0) // Player won game
    {
        //Play win music
        {
            Mix_PauseMusic();
            Mix_PlayChannel(-1, winMusic, 0);
        }

        winScreen.Render(gRenderer);
    }
    else
    {
        // Render Button
        cellBackButton.Render(gRenderer);

        //Render Cell
        for (int i = 0; i < numRows; ++i)
            for (int j = 0; j < numCols; ++j) {
                if(!isDisappear[i][j]) {

                    SDL_RenderCopy(gRenderer, textures[TILE_FRONT], NULL, &cell[i][j].dstRect); // Render background tile
                    
                    SDL_Rect tempDstRect = cell[i][j].dstRect;
                    tempDstRect.x += 2;
                    tempDstRect.y += 2;
                    tempDstRect.w -= 4;
                    tempDstRect.h -= 4;
                    SDL_RenderCopy(gRenderer, cell[i][j].texture, NULL, &tempDstRect);

                    if(isChosen[i][j])
                        SDL_RenderCopy(gRenderer, textures[HIGH_LIGHT], NULL, &cell[i][j].dstRect);
                }
                else 
                    SDL_RenderCopy(gRenderer, textures[HIGH_LIGHT], NULL, &cell[i][j].dstRect);
            }
        
        //Render Trace Segment
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

// the area that show tiles
void createTable() {
    table = {(SCREEN_WIDTH * 8 / 9 - numCols * CELL_WIDTH) / 2 + SCREEN_WIDTH / 9, (SCREEN_HEIGHT - numRows * CELL_HEIGHT) / 2, // position
             numCols * CELL_WIDTH, numRows * CELL_HEIGHT}; // size
}

void createBackButton()
{
    int backButton_Width = 113;
    int backButton_Height = 68;
    SDL_Rect dstRect = {(SCREEN_WIDTH / 9 - backButton_Width) / 2, (SCREEN_HEIGHT - backButton_Height) / 2 , backButton_Width, backButton_Height};
    setCell(cellBackButton, textures[BACK_BUTTON], dstRect);
}

void createWinScreen() 
{
    SDL_Rect dstRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    setCell(winScreen, textures[WIN_SCREEN], dstRect);
}

void processGameMouseDown(int x, int y)
{
    if (Inside(cellBackButton.dstRect, {x, y})) // Check if player go back to menu
    {
        currentScreen = MENU_SCREEN;
        return;
    }

    // Otherwise, find the cell that player click
    for (int i = 0; i < numRows; ++i)
        for (int j = 0; j < numCols; ++j)
            if (!isDisappear[i][j] && Inside(cell[i][j].dstRect, {x, y}))
            {
                isChosen[i][j] = !isChosen[i][j];

                if (isChosen[i][j])
                    posChosen[numChosen++] = {i, j};
                else
                    --numChosen;

                goto done;
            }
done:;

    if (numChosen == 2)
    {
        if (cell[posChosen[0].x][posChosen[0].y].texture == cell[posChosen[1].x][posChosen[1].y].texture && canReach(posChosen[0], posChosen[1]))
        {
            isDisappear[posChosen[0].x][posChosen[0].y] = true;
            isDisappear[posChosen[1].x][posChosen[1].y] = true;

            numRemains -= 2;
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

        isChosen[posChosen[0].x][posChosen[0].y] = false;
        isChosen[posChosen[1].x][posChosen[1].y] = false;
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

//use BFS to find valid path between 2 cell
// idea: par[x][y][z][]
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

                if (u >= 0 && u <= numRows + 1 && v >= 0 && v <= numCols + 1 && (u == 0 || u == numRows + 1 || v == 0 || v == numCols + 1 || isDisappear[u - 1][v - 1] || (u == dst.x && v == dst.y)))
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

                if (u >= 0 && u <= numRows + 1 && v >= 0 && v <= numCols + 1 && (u == 0 || u == numRows + 1 || v == 0 || v == numCols + 1 || isDisappear[u - 1][v - 1] || (u == dst.x && v == dst.y)))
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

// reset for new game
void resetGame() {
    score = 0; // reset score
    numChosen = 0; // no chosen in new game
    segments.clear();
}

void assignLevel(const std::string &lv)
{
    level = lv; // assign level
    resetGame();

    std::ifstream inf(("levels\\" + level + ".txt").c_str());
    
    inf >> numRows >> numCols;
    numRemains = numRows * numCols;
    createTable();

    std::vector<int> id(numRows * numCols / 2);
    for (auto &i : id) i = rand(0, NUM_TILES - 1);

    for (int i = 0; i < numRows; ++i)
        for (int j = 0; j < numCols; ++j)
        {
            int x; inf >> x;

            SDL_Rect dstRect = {j * CELL_WIDTH + table.x, i * CELL_HEIGHT + table.y, TILE_WIDTH, TILE_HEIGHT};
            setCell(cell[i][j], textures[id[x]], dstRect);
            isDisappear[i][j] = isChosen[i][j] = false;
        }

    id.clear();
    id.shrink_to_fit();
    inf.close();
}

void setCell(cellStatus &cell, textureObject tile, SDL_Rect dstRect)
{
    cell.set(tile, dstRect);
}