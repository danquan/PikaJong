#if defined(_WIN64) || defined(_WIN32)
    #include <SDL.h>
#else
    #include <SDL2/SDL.h>
#endif

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
// par[x][y][direction][number_time_change_direction]
// we compress 4 identify index into 1 int-type variable
// row * 2^24 + cols * 2 ^ 16 + dir * 2^3 + number_of_change * 2^0

int numCols, numRows, numRemains;
SDL_Rect table,                          // where to show tiles
    infoTable;                           // where to show informations
cellStatus cell[MAX_ROWS][MAX_COLUMNS];  // status of cells in table
bool isDisappear[MAX_ROWS][MAX_COLUMNS]; // use if tile has been deleted
bool isChosen[MAX_ROWS][MAX_COLUMNS];    // use if tle has been chosen

int numChosen;
SDL_Point posChosen[2];

cellStatus cellBackButton, winScreen;
std::vector<traceSegment> segments;      // use to show trace when 2 tiles are disappeared

extern bool canContinue; // if player can continue the remaining game

std::string level;
int score;

extern type_Screen currentScreen; // type_Screen

void gameRender()
{
    if (numRemains == 0) // Player won game
    {
        // Play win music
        if (Mix_PlayingMusic() != 0)
        {
            Mix_HaltMusic();
            Mix_PlayChannel(-1, chunks[WIN_CHUNK], 0);
        }

        winScreen.Render(gRenderer);
        
        // Render Button
        cellBackButton.Render(gRenderer);
    }
    else
    {
        // Play Music
        if (Mix_PlayingMusic() == 0)
        {
            Mix_PlayChannel(-1, chunks[START_CHUNK], 0);
            Mix_PlayMusic(musics[GAME_LOOP_MUSIC], -1);
        }

        // Render Button
        cellBackButton.Render(gRenderer);

        // render Infotable
        draw_rect_with_alpha(gRenderer, infoTable, 0xff, 0xff, 0xff, 128);

        /*--- RenderScore ---*/
        SDL_Rect tempDstRect = {0, infoTable.y + 15, 0, 0};
        SDL_Texture *tempTexture = text_to_texture(gRenderer, "SCORES", "fonts\\comic-sans-bold.ttf", 30, tempDstRect, {0, 0, 0});
        Render_Texture(gRenderer, // renderer
                        tempTexture, // text
                        {(infoTable.w - tempDstRect.w) / 2 + infoTable.x, tempDstRect.y, tempDstRect.w, tempDstRect.h}); // dstRect

        tempDstRect.y += tempDstRect.h;


        tempTexture = text_to_texture(gRenderer, int_to_string(score), "fonts\\comic-sans-bold.ttf", 30, tempDstRect, {0, 0, 0});
        Render_Texture(gRenderer, // renderer
                        tempTexture, // text
                        {(infoTable.w - tempDstRect.w) / 2 + infoTable.x, tempDstRect.y, tempDstRect.w, tempDstRect.h}); // dstRect
        tempDstRect.y += tempDstRect.h + 20;

        // Render Remaining Tiles
        tempTexture = text_to_texture(gRenderer, "REMAINING", "fonts\\comic-sans-bold.ttf", 30, tempDstRect, {0, 0, 0});
        Render_Texture(gRenderer, // renderer
                        tempTexture, // text
                        {(infoTable.w - tempDstRect.w) / 2 + infoTable.x, tempDstRect.y, tempDstRect.w, tempDstRect.h}); // dstRect
        tempDstRect.y += tempDstRect.h;

        tempTexture = text_to_texture(gRenderer, "TILES", "fonts\\comic-sans-bold.ttf", 30, tempDstRect, {0, 0, 0});
        Render_Texture(gRenderer, // renderer
                        tempTexture, // text
                        {(infoTable.w - tempDstRect.w) / 2 + infoTable.x, tempDstRect.y, tempDstRect.w, tempDstRect.h}); // dstRect
        tempDstRect.y += tempDstRect.h;

        tempTexture = text_to_texture(gRenderer, int_to_string(numRemains), "fonts\\comic-sans-bold.ttf", 30, tempDstRect, {0, 0, 0});
        Render_Texture(gRenderer, // renderer
                        tempTexture, // text
                        {(infoTable.w - tempDstRect.w) / 2 + infoTable.x, tempDstRect.y, tempDstRect.w, tempDstRect.h}); // dstRect

        // Render Cell
        for (int i = 0; i < numRows; ++i)
            for (int j = 0; j < numCols; ++j)
            {
                if (!isDisappear[i][j])
                {
                    SDL_RenderCopy(gRenderer, textures[TILE_FRONT], NULL, cell[i][j].getRect()); // Render background tile

                    tempDstRect = *cell[i][j].getRect();
                    tempDstRect.x += 2; // minimize tile
                    tempDstRect.y += 2; // minimize tile
                    tempDstRect.w -= 4; // minimize tile
                    tempDstRect.h -= 4; // minimize tile
                    SDL_RenderCopy(gRenderer, cell[i][j].getTexture(), NULL, &tempDstRect);

                    if (isChosen[i][j])
                        SDL_RenderCopy(gRenderer, textures[HIGH_LIGHT], NULL, cell[i][j].getRect());
                }
                else
                    SDL_RenderCopy(gRenderer, textures[HIGH_LIGHT], NULL, cell[i][j].getRect());
            }

        // Render Trace Segment
        SDL_SetRenderDrawColor(gRenderer, 0, 204, 0, 200);
        for (int i = (int)segments.size() - 1; ~i; --i) // Draw segments
        {
            segments[i].Draw(gRenderer);

            if (segments[i].Exist() == 0) // Out of time
            {
                segments[i] = segments.back();
                segments.pop_back();
            }
        }
    }
}

void createBackButton()
{
    int backButton_Width = 113;
    int backButton_Height = 68;
    SDL_Rect dstRect = {(SCREEN_WIDTH / 9 - backButton_Width) / 2, (SCREEN_HEIGHT / 9 - backButton_Height) / 2, backButton_Width, backButton_Height};
    cellBackButton.set(textures[BACK_BUTTON], dstRect);
}

void createWinScreen()
{
    SDL_Rect dstRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    winScreen.set(textures[SCREEN_WIN], dstRect);
}

void createGameScreen()
{
    createBackButton();
    createWinScreen();
}

void processGameMouseOver(int x, int y)
{
    if (Inside(*cellBackButton.getRect(), {x, y}))
    {
        cellBackButton.set(textures[BACK_BUTTON_MOUSEOVER], *cellBackButton.getRect());
    }
    else
    {
        cellBackButton.set(textures[BACK_BUTTON], *cellBackButton.getRect());
    }
}

void updateScore(int coef)
{
    numRemains -= 2; // Decrease number of remain tile first

    score += 3 - coef; // 0 -> 3 points, 1 -> 2 points, 3 -> 1 points
}

void processGameMouseDown(int x, int y)
{
    if ((currentScreen == GAME_SCREEN || currentScreen == WIN_SCREEN) && Inside(*cellBackButton.getRect(), {x, y})) // Check if player go back to menu
    {
        currentScreen = MENU_SCREEN;
        canContinue = true;

        if (Mix_PlayingMusic() != 0)
        {
            Mix_HaltMusic();
        }

        return;
    }

    // Otherwise, find the cell that player click
    for (int i = 0; i < numRows; ++i)
        for (int j = 0; j < numCols; ++j)
            if (!isDisappear[i][j] && Inside(*cell[i][j].getRect(), {x, y}))
            {
                isChosen[i][j] = !isChosen[i][j];

                if (isChosen[i][j])
                    posChosen[numChosen++] = {i, j};
                else
                    --numChosen;

                goto done_click;
            }
done_click:;

    if (numChosen == 2)
    {
        if (cell[posChosen[0].x][posChosen[0].y].getTexture() == cell[posChosen[1].x][posChosen[1].y].getTexture())
        {
            doSearch(posChosen[0], posChosen[1]);

            for (int num_change = 0; num_change < 3; ++num_change) // Prio number of change first
                for (int dir = 0; dir < 2; ++dir)
                    if (par[posChosen[1].x + 1][posChosen[1].y + 1][dir][num_change] != -1) // this state, but we need to add 1 to coordinator of poschosen
                    {
                        isDisappear[posChosen[0].x][posChosen[0].y] = true;
                        isDisappear[posChosen[1].x][posChosen[1].y] = true;

                        updateScore(num_change);

                        Trace(posChosen[0], posChosen[1], dir, num_change);
                        // Trace for draw segments
                        goto done_trace;
                    }
        done_trace:;
        }

        isChosen[posChosen[0].x][posChosen[0].y] = false;
        isChosen[posChosen[1].x][posChosen[1].y] = false;
        numChosen = 0;
    }
}

SDL_Point getCenter(SDL_Point coordinate)
{
    if (Inside(table, coordinate))
        return Center(*cell[coordinate.x - 1][coordinate.y - 1].getRect());

    SDL_Rect dst;
    dst.x = coordinate.y < 1 ? table.x - CELL_WIDTH : (coordinate.y > numCols ? table.x + table.w : (coordinate.y - 1) * CELL_WIDTH + table.x);
    dst.y = coordinate.x < 1 ? table.y - CELL_HEIGHT : (coordinate.x > numRows ? table.y + table.h : (coordinate.x - 1) * CELL_HEIGHT + table.y);
    dst.w = CELL_WIDTH;
    dst.h = CELL_HEIGHT;

    return Center(dst);
}

void Trace(SDL_Point src, SDL_Point dst, int dir, int num_change)
{
    ++src.x;
    ++src.y;
    ++dst.x;
    ++dst.y; // Add coordinator by 1

    for (SDL_Point roller = dst; roller.x != src.x || roller.y != src.y;)
    {

        SDL_Point temp = {(par[roller.x][roller.y][dir][num_change] >> 24) & 255,
                          (par[roller.x][roller.y][dir][num_change] >> 16) & 255};

        // getCenter(roller), getCenter(temp);
        segments.emplace_back(getCenter(roller), getCenter(temp), SEGMENT_COUNT_EXIST);

        dst = {(par[roller.x][roller.y][dir][num_change] >> 8) & 255,
               par[roller.x][roller.y][dir][num_change] & 255};
        dir = dst.x;
        num_change = dst.y;

        roller = temp;
    }
}

// use BFS to find valid path between 2 cell
//  idea: par[x][y][z][]
void doSearch(SDL_Point src, SDL_Point dst)
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

        for (int i = 0; i < 2; ++i)
            for (int dir_change = 0; dir_change < 2; ++dir_change)
                if (c.num_change + dir_change < 3)
                {
                    int u = c.x + dx[c.dir ^ dir_change][i],
                        v = c.y + dy[c.dir ^ dir_change][i];

                    if (u >= 0 && u <= numRows + 1 && v >= 0 && v <= numCols + 1 // Inside area
                        && (u == 0 || u == numRows + 1 || v == 0 || v == numCols + 1 || isDisappear[u - 1][v - 1] || (u == dst.x && v == dst.y)))
                    {
                        if (par[u][v][c.dir ^ dir_change][c.num_change + dir_change] == -1)
                        {
                            par[u][v][c.dir ^ dir_change][c.num_change + dir_change] = (c.x << 24) + (c.y << 16) + (c.dir << 8) + (c.num_change << 0);
                            q.emplace(u, v, c.dir ^ dir_change, c.num_change + dir_change);
                        }
                    }
                }
    }
}

// reset for new game
void resetGame()
{
    score = 0;     // reset score
    numChosen = 0; // no chosen in new game
    segments.clear();
}

// the area that show tiles
void createTable()
{
    table = {(SCREEN_WIDTH * 8 / 9 - numCols * CELL_WIDTH) / 2 + SCREEN_WIDTH / 9, (SCREEN_HEIGHT - numRows * CELL_HEIGHT) / 2, // position
             numCols * CELL_WIDTH, numRows * CELL_HEIGHT};                                                                      // size
}

// the area that show informations
void createInfoTable() {
    infoTable = {(table.x - 190) / 2, (SCREEN_HEIGHT - 300) / 2, 190, 300};
}

void assignLevel(const std::string &lv)
{
    level = lv; // assign level
    resetGame();

    std::ifstream inf(("levels\\" + level + ".txt").c_str());

    inf >> numRows >> numCols;
    numRemains = numRows * numCols;
    createTable();
    createInfoTable();

    for (int i = 0; i < numRows; ++i)
        for (int j = 0; j < numCols; ++j)
        {
            int x;
            inf >> x;

            SDL_Rect dstRect = {j * CELL_WIDTH + table.x, i * CELL_HEIGHT + table.y, TILE_WIDTH, TILE_HEIGHT}; // TILE Size is not same as CELL Size
            cell[i][j].set(textures[x], dstRect);
            isDisappear[i][j] = isChosen[i][j] = false;
        }

    inf.close();
}