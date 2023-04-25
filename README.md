# PikaJong, developed by Nguyen Dang Quan (aka Lam lai cuoc doi)

This is a game that I created as a personal project. It's a simple game that easy to play for all ages. The game is built with C++ and uses SDL 2.0.

# Installation

Prerequisites:
- GNU C++
- SDL 2.0 (In Windows, I've copied it to the source code)

## Windows

- Clone source code
- Open command promt or powershell, direct to the folder that you've clone code and type the following command to run compiling:

    >**./make**
- After compiling, please check for the existence of executable file name **PikaJong.exe**
- Then type the following command to run game:
    - If you use command promt (cmd) then type:
        >**PikaJong.exe**
    - If you use powershell then type:
        >**./PikaJong**

# Game play

Player(s) need to choose 2 tiles that:
- The characters print on 2 tiles are the same
- It's should have **at least one** way to connect 2 tiles using no more than 3 consecutive segments without intersect any other tile

Those chosen tiles will disappear immediately

# Add more levels

My game allows you to add your own levels; you follow the below guideline:
- Create a file with name `<level_name>.txt` in folder `levels`
- Add one more line with content `<level_name>` in file `list-levels.text` in the same folder

The file `<level_name>.txt` consists of:
- The first line contains two integers $m, n$ ($m\le 11, n\le 20$) - number of rows and number of columns
- The next $m$ lines, in each line there are $n$ integers:
    - Each one has value from $0$ to $32$
    - Two cells have same number should have the same characters (The chosen character is followed by the order of tiles in `list_tiles.txt`)

# Support

If you encounter any issues with the game or have any questions, please contact me at <dangquanattvhouse@gmail.com>. I'll do my best to help you out!