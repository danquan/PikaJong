# PikaJong, developed by Nguyen Dang Quan (aka Lam lai cuoc doi)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

This is a game that I created as a personal project. It's a simple game that easy to play for all ages. The game is built with C++ and uses SDL 2.0.


# Installation

Prerequisites:
- GNU C++
- SDL 2.0 :
    - In Windows, I've copied it to the source code
    - In Linux, please follow these tutorials to install:
        - [SDL 2.0](https://lazyfoo.net/tutorials/SDL/01_hello_SDL/linux/index.php)
        - [SDL Image](https://lazyfoo.net/tutorials/SDL/06_extension_libraries_and_loading_other_image_formats/linux/index.php)
        - [SDL Mixer](https://lazyfoo.net/tutorials/SDL/21_sound_effects_and_music/index.php)
        - [SDL TTF](https://lazyfoo.net/tutorials/SDL/16_true_type_fonts/index.php)

## Windows

- Download and extract source code
- Open command promt or powershell, direct to the folder that you've extracted code and type the following command to do the compiling:
    - If you use command promt (cmd) then type:
        >**make**
    - If you use powershell then type:
        >**./make**
- After compiling, please check for the existence of executable file name **PikaJong.exe**
- Then type the following command to run game:
    - If you use command promt (cmd) then type:
        >**PikaJong**
    - If you use powershell then type:
        >**./PikaJong**

## Linux
- Download and extract source code
- Open terminal, direct to the folder that you've extracted code and type the following command to do the compiling:
    >**./make.sh**
- After compiling, please check for the existence of executable file name **PikaJong**
- Then type the following command to run game:
    >**./PikaJong**
    
# Game play

Player(s) need to choose 2 tiles that:
- The characters print on 2 tiles are the same
- It's should have **at least one** way to connect 2 tiles using no more than 3 consecutive segments without intersect any other tile

Those chosen tiles will disappear immediately

# Demo

These screenshots are about my game:

<p align="center">
  <img src="./images/demo_menu.png" alt="Menu"/>
</p>

In game screen:

<p align="center">
  <img src="./images/demo_game_play.png" alt="Game Screen"/>
</p>

# Add more levels

My game allows you to add your own levels; you follow the below guideline:
- Create a file with name `<level_name>.txt` in folder `levels`
- Add one more line with content `<level_name>` in file `list-levels.text` in the same folder

The file `<level_name>.txt` consists of:
- The first line contains two integers $m, n$ ($m\le 11, n\le 20$) - number of rows and number of columns
- The next $m$ lines, in each line there are $n$ integers:
    - Each one has value from $0$ to $32$
    - Two cells have same number should have the same character (The chosen character is followed by the order of tiles in `list_tiles.txt`)

# Support

If you encounter any issues with the game or have any questions, please contact me at <dangquanattvhouse@gmail.com>. I'll do my best to help you out!