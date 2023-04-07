# Game Pika Chược, develope by Nguyen Dang Quan (aka Lam lai cuoc doi)

<h1>Luật chơi</h1>

Có thể tùy biến levels; cụ thể, để tạo level mới bạn cần:
- Thêm một file txt có dạng <ten_level>.txt vào thư mục levels
- Thay đổi tên của level thành <ten_level> trong khi gọi đến hàm assignLevel() trong file main.cpp
Nội dung của file <ten_level>.txt bao gồm:
- Dòng đầu tiên chứa hai số nguyên dương $m, n$ ($m\le 11, n\le 20$) là số hàng và số cột của bảng
- $m$ dòng tiếp, mỗi dòng chứa $n$ số nguyên dương mô tả bảng đã cho; trong đó:
    - Mỗi số nguyên từ $0$ đến $\frac{m\times n}{2} - 1$ xuât hiện chính xác 2 lần
    - Hai ô có số giống nhau thì mang hình giống nhau (Hình nào chương trình sẽ tự quyết định theo random)