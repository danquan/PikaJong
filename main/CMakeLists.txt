include_directories(
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/lib/x86_64-w64-mingw32-SDL/include
)

add_library(controller_lib
main.h
controller.cpp controller.h
gamecontroller.cpp gamecontroller.h)

target_link_libraries(controller_lib graphic_lib sound_lib)