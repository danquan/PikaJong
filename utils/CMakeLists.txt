include_directories(
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/lib/x86_64-w64-mingw32-SDL/include
)

add_library(utils_lib
jsonhelper.h jsonhelper.cpp
utils.h utils.cpp
)