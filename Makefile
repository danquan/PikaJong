main = main.cpp
textures = textures.cpp
game_run = game_run.cpp
menu = menu.cpp
exe_file = pikajong

# command
all : 
	g++ -g $(textures) $(main) $(game_run) $(menu) -I ".\x86_64-w64-mingw32-SDL\include\SDL2" -L ".\x86_64-w64-mingw32-SDL\lib" -w -O2 -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -o $(exe_file)
