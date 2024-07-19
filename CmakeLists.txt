##################################################################
# Pikajong cmake build definition
# Copyright (c) 2024 Nguyen Dang Quan
##################################################################


cmake_minimum_required(VERSION 3.10)

# Set Compiler
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)

project(Pikajong VERSION 2.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Link Directories

# Set flag C++
## Set Compiler flag C++
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -w -O2")

add_subdirectory(main)
add_subdirectory(graphic)
add_subdirectory(sound)

# Include header library
include_directories(
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/lib/x86_64-w64-mingw32-SDL/include
)

# Thư mục chứa library
link_directories(    
    ${CMAKE_SOURCE_DIR}/lib/x86_64-w64-mingw32-SDL/lib
)

# Tạo file executable
add_executable(
    pikajong
    ${CMAKE_SOURCE_DIR}/main/main.cpp
)

# Nối các code lại với nhau
target_link_libraries(pikajong
    controller_lib
    graphic_lib
    sound_lib
)

# Link các thư viện SDL2 vào
target_link_libraries(pikajong
    mingw32
    SDL2main
    SDL2
    SDL2_image
    SDL2_mixer
    SDL2_ttf
)

# Sao chép tệp DLL vào thư mục thực thi
add_custom_command(
    TARGET pikajong POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/lib/x86_64-w64-mingw32-SDL/bin/SDL2.dll"
        $<TARGET_FILE_DIR:pikajong>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/lib/x86_64-w64-mingw32-SDL/bin/SDL2_mixer.dll"
        $<TARGET_FILE_DIR:pikajong>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/lib/x86_64-w64-mingw32-SDL/bin/SDL2_ttf.dll"
        $<TARGET_FILE_DIR:pikajong>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/lib/x86_64-w64-mingw32-SDL/bin/SDL2_image.dll"
        $<TARGET_FILE_DIR:pikajong>
)