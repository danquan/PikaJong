set OBJS=main.cpp textures.cpp game_run.cpp menu.cpp
set OBJ_NAME=PikaJong.exe
set COMPILER_FLAGS=-std=c++14 -w -O2
set LINKER_FLAGS=-lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
set INCLUDE_DIR=-I ".\x86_64-w64-mingw32-SDL\include\SDL2" -L ".\x86_64-w64-mingw32-SDL\lib"

g++ -g %OBJS% %COMPILER_FLAGS% %INCLUDE_DIR% %LINKER_FLAGS% -o %OBJ_NAME%