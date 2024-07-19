
include_directories(
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/lib/x86_64-w64-mingw32-SDL/include
)

add_library(graphic_lib
graphic.cpp graphic.h
jong.cpp jong.h
screen.cpp screen.h
button.cpp button.h
)