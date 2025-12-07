<h1 align="center">TETRIS GAME – Đồ án cuối kỳ</h1>

Dự án là một trò chơi Tetris dạng console/desktop, chạy trên Windows, Linux và macOS, được viết bằng C++. 
Người chơi điều khiển các khối rơi xuống, xoay và sắp xếp để tạo thành hàng hoàn chỉnh, ghi điểm và tránh cho chồng khối chạm tới đỉnh màn hình.

---

## 1. Thông tin nhóm

• **Môn học:** SS004.Q12 – Kỹ năng nghề nghiệp  
• **Tên đồ án:** TETRIS GAME – Đồ án cuối kỳ  
• **Thành viên:**  
– Nguyễn Việt Anh – 24520121  
– Lê Minh Hiếu – 24520494  
– Trần Nguyễn Thuận Phát – 24521319  
– Cao Minh Huy – 24520652  
– Dương Tú Thanh – 24521619  

---

## 2. Mô tả ngắn gọn

Trò chơi **TETRIS** gồm:

• Cơ chế tạo và rơi các khối (Tetromino).  
• Xoay và di chuyển khối theo phím mũi tên hoặc WASD.  
• Xóa hàng khi đầy, cộng điểm và tăng tốc độ theo cấp độ.  
• Lưu điểm cao (tùy chọn).
## 3. Cách chơi (Gameplay)

1. Khi chạy chương trình, một khối gạch (Tetromino) sẽ xuất hiện ở phía trên màn hình, vị trí ngẫu nhiên và bắt đầu rơi xuống.

2. Dùng các phím W/A/S/D để điều khiển:
   - A: Di chuyển sang trái
   - D: Di chuyển sang phải

3. Khi một hàng được lấp đầy hoàn toàn:
   - Hàng đó sẽ biến mất.
   - Các hàng phía trên sẽ rơi xuống.
   - Điểm số tăng thêm 100 cho mỗi hàng bị xóa.
   - Tốc độ rơi sẽ tăng lên mỗi khi một hàng bị xóa

4. Nếu khối gạch rơi chạm đáy hoặc chạm vào các khối đã cố định:
   - Khối sẽ được cố định lại.
   - Một khối mới xuất hiện và tiếp tục rơi.

5. Trò chơi kết thúc khi các khối gạch chồng lên đến đỉnh màn hình.
   



