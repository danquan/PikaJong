#include <bits/stdc++.h>
using namespace std;

    mt19937 Rand(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    long long rand(long long l, long long r) {
        return Rand() % (r - l + 1) + l;
    }
    
int m, n;
int a[102][102];
int par[102][102][2][3]; //(x, y, direction, num_change_direction)

int dx[2][2] = {{0, 0}, {-1, 1}},
    dy[2][2] = {{-1, 1}, {0, 0}};

bool canReach(int x, int y, int z, int t) {
    memset(par, -1, sizeof par);
    ++x; ++y; ++z; ++t; // Add coordinator by 1

    struct Tque {
        int x, y, dir, num_change;
        Tque(int x = 0, int y = 0, int dir = 0, int num_change = 0): x(x), y(y), dir(dir), num_change(num_change){}
    };
    queue<Tque> q;

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
                
                if(u >= 0 && u <= m + 1 && v >= 0 && v <= n + 1 && (u == 0 || u == m + 1 || v == 0 || v == n + 1 || a[u - 1][v - 1] != 0 || (u == z && v == t))) {
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
                
                if(u >= 0 && u <= m + 1 && v >= 0 && v <= n + 1 && (u == 0 || u == m + 1 || v == 0 || v == n + 1 || a[u - 1][v - 1] != 0|| (u == z && v == t))) {
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

int32_t main()
{
    // Read Input
    {
        cout << "Please type number of Rows: ";
        cin >> m;
        cout << "and number of Columns: ";
        cin >> n;

        if ((m * n) & 1)
        {
            cout << "Not valid, sorry";
            return 0;
        }

        cout << "Thank you, your table look like:\n";
    }

    // Proccess Table and Print
    {
        cout << m << " " << n << "\n";
        
        vector<pair<int, int>> res;

        for(int i = 0; i < m; ++i)
            for(int j = 0; j < n; ++j)
                res.emplace_back(i, j);
        
        shuffle(res.begin(), res.end(), Rand);
        shuffle(res.begin(), res.end(), Rand);
        shuffle(res.begin(), res.end(), Rand);
        shuffle(res.begin(), res.end(), Rand);
        shuffle(res.begin(), res.end(), Rand);
        shuffle(res.begin(), res.end(), Rand);
        shuffle(res.begin(), res.end(), Rand);
        shuffle(res.begin(), res.end(), Rand);
        shuffle(res.begin(), res.end(), Rand);
        shuffle(res.begin(), res.end(), Rand);

        int cnt = 0;

        while(!res.empty()) {
            int j = rand(0, res.size() - 1);
            pair<int, int> cell_1 = res[j];
            res[j] = res.back();
            res.pop_back();

            for(int j = (int)res.size() - 1; ~j; --j)
                if(canReach(cell_1.first, cell_1.second, res[j].first, res[j].second)) {
                    a[cell_1.first][cell_1.second] = a[res[j].first][res[j].second] = ++cnt;
                    //cerr << cell_1.first << " " << cell_1.second << " " << res[j].first << " " << res[j].second << ": " << cnt << "\n";
                    res[j] = res.back();
                    res.pop_back();
                    break;
                }
        }

        for(int i = 0; i < m; ++i)
            for(int j = 0; j < n; ++j)
                cout << a[i][j] - 1 << (j == n - 1 ? "\n" : " ");
    }
}