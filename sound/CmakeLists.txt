include_directories(
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/lib/x86_64-w64-mingw32-SDL/include
)

add_library(sound_lib
music.cpp music.h
sound.cpp sound.h
chunk.cpp chunk.h
)