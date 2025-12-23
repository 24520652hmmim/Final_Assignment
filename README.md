# 🎮 TETRIS GAME – Đồ án cuối kỳ

<div align="center">
  <img src="https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white" alt="C++ Badge"/>
  <img src="https://img.shields.io/badge/Windows-0078D4?style=for-the-badge&logo=windows&logoColor=white" alt="Windows"/>
  <img src="https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black" alt="Linux"/>
  <img src="https://img.shields.io/badge/macOS-000000?style=for-the-badge&logo=apple&logoColor=white" alt="macOS"/>
  <br>
  <img src="https://img.shields.io/badge/Status-Completed-success?style=flat-square" alt="Status"/>
  <img src="https://img.shields.io/badge/Version-1.0-blue?style=flat-square" alt="Version"/>
</div>

<div align="center">
  <pre>
  ████████╗███████╗████████╗██████╗ ██╗███████╗
  ╚══██╔══╝██╔════╝╚══██╔══╝██╔══██╗██║██╔════╝
     ██║   █████╗     ██║   ██████╔╝██║███████╗
     ██║   ██╔══╝     ██║   ██╔══██╗██║╚════██║
     ██║   ███████╗   ██║   ██║  ██║██║███████║
     ╚═╝   ╚══════╝   ╚═╝   ╚═╝  ╚═╝╚═╝╚══════╝
  </pre>
</div>

## 📋 Mục lục
- [🚀 Giới thiệu](#-giới-thiệu)
- [📁 Cấu trúc thư mục](#-cấu-trúc-thư-mục)
- [✨ Tính năng](#-tính-năng)
- [🛠️ Công nghệ sử dụng](#️-công-nghệ-sử-dụng)
- [📦 Cài đặt](#-cài-đặt)
- [🎮 Cách chơi](#-cách-chơi)
- [👥 Thông tin nhóm](#-thông-tin-nhóm)
- [📸 Ảnh chụp màn hình](#-ảnh-chụp-màn-hình)
- [🔮 Phát triển tương lai](#-phát-triển-tương-lai)
- [📄 Giấy phép](#-giấy-phép)

---

## 🚀 Giới thiệu

**Chào mừng đến với thế giới Tetris đầy màu sắc và kịch tính!** 🎉

Đây là dự án **Tetris Game** – đồ án cuối kỳ môn SS004.Q12, được phát triển bởi nhóm sinh viên với niềm đam mê lập trình. Trò chơi được code hoàn toàn bằng C++ thuần, không sử dụng thư viện bên ngoài, chứng minh khả năng xử lý logic phức tạp và tối ưu hóa hiệu suất.

**Tại sao dự án này đặc biệt?**
- 🎯 **Thách thức kỹ thuật**: Triển khai game loop, collision detection, và rendering trên console.
- 🔥 **Hiệu suất cao**: Chạy mượt mà trên đa nền tảng Windows, Linux, macOS.
- 🧠 **Logic tinh tế**: Thuật toán xoay khối, xóa hàng, và quản lý trạng thái game.
- 💡 **Học hỏi thực tế**: Áp dụng kiến thức C++ vào dự án thực tế.

---

## 📁 Cấu trúc thư mục

Dưới đây là cấu trúc tổng quan của dự án:

```
Final_Assignment/
├── .git/                 # Thư mục Git repository (ẩn)
├── .gitignore           # File cấu hình bỏ qua các file không cần thiết
├── .vscode/             # Cài đặt VS Code (settings, launch.json)
├── README.md            # Tài liệu dự án (file này!)
├── TERRIS.cpp           # Code nguồn chính của trò chơi
└── TERRIS.exe           # File thực thi đã biên dịch (Windows)
```

### Giải thích chi tiết:
- **`.git/`**: Chứa dữ liệu version control của Git.
- **`.gitignore`**: Loại trừ file tạm thời, build artifacts khỏi Git.
- **`.vscode/`**: Cấu hình editor cho VS Code (debug, build tasks).
- **`README.md`**: Tài liệu hướng dẫn, thông tin dự án.
- **`TERRIS.cpp`**: File code nguồn duy nhất chứa toàn bộ logic game.
- **`TERRIS.exe`**: Binary executable sau khi compile (chỉ trên Windows).

**Lưu ý**: File `.exe` không được commit vào Git, chỉ tạo locally khi build.

---

## ✨ Tính năng

Trò chơi **TETRIS** với những cơ chế cực kỳ hấp dẫn:

- 🔲 **Tạo và rơi khối**: 7 loại Tetromino ngẫu nhiên, rơi với tốc độ tăng dần.
- 🎮 **Điều khiển linh hoạt**: Phím WASD hoặc mũi tên – di chuyển, xoay như siêu anh hùng!
- 🗑️ **Xóa hàng bùng nổ**: Hàng đầy? BOOM! Biến mất, điểm tăng vọt, tốc độ tăng chóng mặt!
- 🏆 **Hệ thống điểm**: Điểm số, cấp độ, và lưu high score.
- 🌈 **Giao diện console**: ASCII art đẹp mắt, dễ chơi mọi lúc mọi nơi.
- 🔄 **Tương thích đa nền**: Windows, Linux, macOS – không lo!

---

## 🛠️ Công nghệ sử dụng

- **Ngôn ngữ**: C++ (C++11 trở lên)
- **Thư viện**: Chỉ sử dụng STL (Standard Template Library)
- **Công cụ build**: g++ (GCC) hoặc Visual Studio
- **Nền tảng**: Console/Desktop, đa nền tảng

---

## 📦 Cài đặt

### Yêu cầu hệ thống
- C++ Compiler (g++ khuyến nghị)
- Windows/Linux/macOS

### Hướng dẫn cài đặt

1. **Clone repository**:
   ```bash
   git clone https://github.com/your-username/tetris-game.git
   cd tetris-game
   ```

2. **Compile chương trình**:
   ```bash
   g++ TERRIS.cpp -o tetris -std=c++11
   ```

3. **Chạy trò chơi**:
   ```bash
   ./tetris
   ```

**Lưu ý**: Trên Windows, sử dụng `g++ TERRIS.cpp -o tetris.exe` và chạy `tetris.exe`.

---

## 🎮 Cách chơi

### Bắt đầu hành trình!
1. **Khởi động**: Chạy chương trình và xem khối Tetromino đầu tiên xuất hiện như siêu sao! 🌟

2. **Điều khiển như boss**:
   - ⬅️ **A**: Sang trái nhanh như gió!
   - ➡️ **D**: Sang phải mạnh mẽ!
   - 🔄 **W**: Xoay khối 90 độ.
   - ⬇️ **S**: Rơi nhanh như tên lửa!

3. **Xóa hàng đỉnh cao**: Hàng đầy?
   - **POOF!** Hàng biến mất trong chớp mắt!
   - Các hàng trên rơi xuống như thác đổ!
   - **+100 điểm** mỗi hàng – giàu nhanh chóng!
   - Tốc độ tăng dần, adrenaline dâng trào!

4. **Kết thúc kịch tính**: Khối chồng đỉnh? GAME OVER! Thử lại để phá kỷ lục! 🔥

### Mục tiêu: Đạt điểm cao nhất có thể!

---

## 👥 Thông tin nhóm

| **Môn học** | SS004.Q12 – Kỹ năng nghề nghiệp |
|-------------|----------------------------------|
| **Tên đồ án** | TETRIS GAME – Đồ án cuối kỳ |
| **Giảng viên hướng dẫn** | ThS Nguyễn Văn Toàn |
| **Thời gian thực hiện** | Tháng 12/2025 |

### Thành viên nhóm siêu cấp:
- 👨‍💻 **Nguyễn Việt Anh** – 24520121 (Team Leader, Core Logic)
- 👨‍💻 **Lê Minh Hiếu** – 24520494 (Game Mechanics, Collision Detection)
- 👨‍💻 **Trần Nguyễn Thuận Phát** – 24521319 (UI/Console Rendering, Input Handling)
- 👨‍💻 **Cao Minh Huy** – 24520652 (Score System, File I/O)
- 👨‍💻 **Dương Tú Thanh** – 24521619 (Testing, Documentation, Optimization)

**Cảm ơn thầy Nguyễn Văn Toàn đã hướng dẫn tận tình! 🙏**

---

## 📸 Ảnh chụp màn hình

*(Thêm ảnh screenshot của game khi có)*

<div align="center">
  <img src="screenshot1.png" alt="Gameplay Screenshot" width="400"/>
  <p><em>Gameplay chính với khối Tetromino</em></p>
</div>

---

## 🔮 Phát triển tương lai

- 🎨 **Giao diện đồ họa**: Chuyển sang SDL hoặc SFML.
- 🎵 **Âm thanh**: Thêm nhạc nền và hiệu ứng âm thanh.
- 🌐 **Multiplayer**: Chơi online với bạn bè.
- 📱 **Mobile version**: Port sang Android/iOS.
- 🤖 **AI Bot**: Chơi với máy.

---

## 📄 Giấy phép

Dự án này được phát hành dưới giấy phép MIT. Xem file `LICENSE` để biết thêm chi tiết.

---

<div align="center">
  <h2 style="color: #FF6B6B;">Chúc bạn chinh phục đỉnh cao Tetris! 🏔️🎊</h2>
  <p><strong>Hãy tải về và chơi ngay! 🚀</strong></p>
  <p>Made with ❤️ by Team Tetris</p>
</div>



