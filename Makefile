main = main.cpp
tiles = tiles.cpp
game_run = game_run.cpp
exe_file = mahjong

# command
all : 
	g++ -g $(tiles) $(main) $(game_run) -I "C:\Program Files\CodeBlocks\MinGW\x86_64-w64-mingw32-SDL\include\SDL2" -L "C:\Program Files\CodeBlocks\MinGW\x86_64-w64-mingw32-SDL\lib" -w -O2 -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -o $(exe_file)
