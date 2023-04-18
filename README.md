# Game Pika Chược, develope by Nguyen Dang Quan (aka Lam lai cuoc doi)

<h1>Cài đặt</h1>

Yêu cầu: 
- GNU C++
- Cmake
- SDL 2.0

<h2>Windows</h2>
- Clone mã nguồn
- Mở cửa sổ lệnh, điều hướng tới thư mục vừa tải xuống và nhập dòng lệnh:
**make**
- Sau đó trong thư mục sẽ xuất hiện một file là *PikaJong.exe*, đây chính là file chạy game, gõ vào dòng lệnh câu lệnh:
**./PikaJong**

<h1>Luật chơi</h1>

Tại mỗi thời điểm, người chơi cần chọn ra 2 ô sao cho:
- Hình ghi trên hai ô này là giống nhau
- Tồn tại các đoạn thẳng tạo thành không quá 3 đường gấp khúc nối giữa hai ô
Khi đó, hai ô ấy sẽ biến mất

<h1> Thêm Level </h1>

Có thể tùy biến levels; cụ thể, để tạo level mới bạn cần:
- Thêm một file txt có dạng <ten_level>.txt vào thư mục levels
- Thêm một dòng chứa <ten_level> vào file list-levels.text
Nội dung của file <ten_level>.txt bao gồm:
- Dòng đầu tiên chứa hai số nguyên dương $m, n$ ($m\le 11, n\le 20$) là số hàng và số cột của bảng
- $m$ dòng tiếp, mỗi dòng chứa $n$ số nguyên không âm mô tả bảng đã cho; trong đó:
    - Mỗi số nguyên có giá trị từ $0$ đến $32$
    - Hai ô có số giống nhau thì mang hình giống nhau (Hình được in ra sẽ lấy theo thứ tự trong file list_tiles.txt)