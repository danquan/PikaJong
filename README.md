# PikaJong, developed by Nguyen Dang Quan (aka Lam lai cuoc doi)

# Installation

Requirements:
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

# Thêm Level

Có thể tùy biến levels; cụ thể, để tạo level mới bạn cần:
- Thêm một file txt có dạng `<ten_level>.txt` vào thư mục levels
- Thêm một dòng chứa `<ten_level>` vào file `list-levels.text`

Nội dung của file `<ten_level>.txt` bao gồm:
- Dòng đầu tiên chứa hai số nguyên dương $m, n$ ($m\le 11, n\le 20$) là số hàng và số cột của bảng
- $m$ dòng tiếp, mỗi dòng chứa $n$ số nguyên không âm mô tả bảng đã cho; trong đó:
    - Mỗi số nguyên có giá trị từ $0$ đến $32$
    - Hai ô có số giống nhau thì mang hình giống nhau (Hình được in ra sẽ lấy theo thứ tự trong file `list_tiles.txt`)