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

const int dx[2][2] = {{0, 0}, {-1, 1}}, // Use for
          dy[2][2] = {{-1, 1}, {0, 0}}; // BFS Search
int par[MAX_ROWS + 2][MAX_COLUMNS + 2][2][3]; // for BFS Search

int numCols, numRows, numRemains;
cellStatus cell[MAX_ROWS][MAX_COLUMNS]; // status of cells in table

int numChosen;
std::pair<int, int> posChosen[2];

SDL_Texture *last_match; // The mahjong tile that player has just match 
SDL_Rect last_match_pos; // Where to display

std::string level;

extern type_Screen currentScreen; // type_Screen

void gameRender(SDL_Renderer *gRenderer) {

    if(numRemains == 0) // Player won game
    { 
        SDL_Rect dstRect = {(SCREEN_WIDTH - win_Screen.w) / 2, (SCREEN_HEIGHT - win_Screen.h) / 2, win_Screen.w, win_Screen.h};
        SDL_RenderCopy(gRenderer, win_Screen.getTexture(), NULL, &dstRect);
    }
    else 
    {
        SDL_RenderCopy(gRenderer, last_match, NULL, &last_match_pos);

        for(int i = 0; i < numRows; ++i)
            for(int j = 0; j < numCols; ++j) 
                if( !cell[i][j].empty() ) {
                    
                    assert(cell[i][j].tile != NULL);
                    SDL_RenderCopy(gRenderer, cell[i][j].getTexture(), NULL, &cell[i][j].dstRect);

                    if(cell[i][j].getCheckChosen())
                        SDL_RenderCopy(gRenderer, chosen_Highlight, NULL, &cell[i][j].dstRect);
                }
                else 
                    SDL_RenderCopy(gRenderer, chosen_Highlight, NULL, &cell[i][j].dstRect);
    }
}

void processGameMouseDown(int x, int y) {

    for(int i = 0; i < numRows; ++i)
        for(int j = 0; j < numCols; ++j) 
            if(cell[i][j].canClick() && Inside(cell[i][j].dstRect, {x, y})) {

                if( cell[i][j].click() ) {
                    posChosen[numChosen++] = {i, j};
                }
                else {
                    assert(numChosen == 1);
                    --numChosen;
                }

                goto done;
            }
    done:;

    if(numChosen == 2) {
        if(cell[posChosen[0].first][posChosen[0].second].tile == cell[posChosen[1].first][posChosen[1].second].tile
            &&  canReach(posChosen[0].first, posChosen[0].second, posChosen[1].first, posChosen[1].second)) {
            
            cell[posChosen[0].first][posChosen[0].second].disAppear();
            cell[posChosen[1].first][posChosen[1].second].disAppear();
        
            numRemains -= 2;
            last_match = cell[posChosen[0].first][posChosen[0].second].getTexture();
        }

        
        cell[posChosen[0].first][posChosen[0].second].click();
        cell[posChosen[1].first][posChosen[1].second].click();
        numChosen = 0;
    }
}

bool canReach(int x, int y, int z, int t) {
    memset(par, -1, sizeof par);
    ++x; ++y; ++z; ++t; // Add coordinator by 1

    struct Tque {
        int x, y, dir, num_change;
        Tque(int x = 0, int y = 0, int dir = 0, int num_change = 0): x(x), y(y), dir(dir), num_change(num_change){}
    };
    std::queue<Tque> q;

    par[x][y][0][0] = par[x][y][1][0] = 0;
    q.emplace(x, y, 0, 0);
    q.emplace(x, y, 1, 0);

    while(!q.empty()) {
        Tque c = q.front();
        q.pop();

        if(c.x == z && c.y == t) 
            return true;

        for(int i = 0; i < 2; ++i) {
            // same dir
            {
                int u = c.x + dx[c.dir][i],
                    v = c.y + dy[c.dir][i];
                
                if(u >= 0 && u <= numRows + 1 && v >= 0 && v <= numCols + 1 && (u == 0 || u == numRows + 1 || v == 0 || v == numCols + 1 || !cell[u - 1][v - 1].isAppear || (u == z && v == t))) {
                    if(par[u][v][c.dir][c.num_change] == -1) {
                        par[u][v][c.dir][c.num_change] = 0;
                        q.emplace(u, v, c.dir, c.num_change);
                    }
                } 
            }
            
            // different dir
            if(c.num_change < 2){
                int u = c.x + dx[c.dir ^ 1][i],
                    v = c.y + dy[c.dir ^ 1][i];
                
                if(u >= 0 && u <= numRows + 1 && v >= 0 && v <= numCols + 1 && (u == 0 || u == numRows + 1 || v == 0 || v == numCols + 1 || !cell[u - 1][v - 1].isAppear|| (u == z && v == t))) {
                    if(par[u][v][c.dir ^ 1][c.num_change + 1] == -1) {
                        par[u][v][c.dir ^ 1][c.num_change + 1] = 0;
                        q.emplace(u, v, c.dir ^ 1, c.num_change + 1);
                    }
                } 
            }

        }
    }

    return false; // can't reach
}

void assignLevel(const std::string &lv) {
    level = lv;
    std::ifstream inf( ("levels\\" + level + ".txt").c_str() );

    inf >> numRows >> numCols;
    
    int tableWidth =  numCols * CELL_WIDTH;
    int tableHeight = numRows * CELL_HEIGHT;
    int leftX = (SCREEN_WIDTH - tableWidth) / 2;
    int leftY = (SCREEN_HEIGHT - tableHeight) / 2;

    last_match = chosen_Highlight;
    last_match_pos = {(leftX - TILE_WIDTH) / 2, (leftY + tableHeight - TILE_HEIGHT) / 2, TILE_WIDTH, TILE_HEIGHT};

    numRemains = numRows * numCols;
    std::vector<int> id(numRows * numCols / 2);
    for(auto &i : id) i = rand(0, MAX_NUM_TILES - 1);

    for(int i = 0; i < numRows; ++i)
        for(int j = 0; j < numCols; ++j) {
            int x; inf >> x;
            
            SDL_Rect dstRect = {j * CELL_WIDTH + leftX, i * CELL_HEIGHT + leftY, TILE_WIDTH, TILE_HEIGHT};
            setCell(i, j, &tile[id[x]], dstRect);
        }

    id.clear();
    id.shrink_to_fit();
    numChosen = 0; // For new game
    inf.close();
}

void resetCell(int x, int y) {
    cell[x][y].reset();
}

void setCell(int x, int y, textureObject *tile, SDL_Rect dstRect) {
    cell[x][y].set(tile, dstRect);
}