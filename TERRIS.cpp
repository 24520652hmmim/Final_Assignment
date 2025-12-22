#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <mmsystem.h>
#include <string>

using namespace std;

#pragma comment(lib, "winmm.lib")

// === THAY ĐỔI KÍCH THƯỚC Ở ĐÂY ===
#define H 22  // Cao 22
#define W 22  // Rộng 22
// =================================

#define START_X 4
#define START_Y 2

char board[H][W] = {};
int score = 0;
int dropDelay = 300;
bool isPaused = false;
int comboCount = 0;

void hideCursor() {
    CONSOLE_CURSOR_INFO ci;
    ci.dwSize = 1;
    ci.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ci);
}

void gotoxy(int x, int y) {
    COORD c = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void drawBorderBox(int x, int y, int w, int h) {
    setColor(7);
    gotoxy(x, y); cout << char(201);
    for (int i = 0; i < w; i++) cout << char(205);
    cout << char(187);

    for (int i = 0; i < h; i++) {
        gotoxy(x, y + 1 + i); cout << char(186);
        gotoxy(x + w + 1, y + 1 + i); cout << char(186);
    }

    gotoxy(x, y + h + 1); cout << char(200);
    for (int i = 0; i < w; i++) cout << char(205);
    cout << char(188);
}

inline bool inPlayable(int tx, int ty) {
    return (tx >= 1 && tx <= W - 2 && ty < H - 1);
}

int menu() {
    while (true) {
        system("cls");
        setColor(11);
        cout << "\n\n";
        cout << "    TETRIS GAME \n";
        cout << "   ==============\n\n";
        setColor(7);
        cout << "  1. Start Game \n";
        cout << "  2. Speed: Slow\n";
        cout << "  3. Speed: Normal\n";
        cout << "  4. Speed: Fast\n";
        cout << "  5. Exit\n\n";
        cout << "  Select: ";

        char c = _getch();
        if (c >= '1' && c <= '5') return c - '0';
    }
}

class Piece {
public:
    char shape[4][4];
    int x, y;
    int colorCode;

    Piece() {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                shape[i][j] = ' ';
        // Căn chỉnh vị trí xuất hiện ở giữa bảng
        x = W / 2 - 2;
        y = 0;
        colorCode = 7;
    }

    virtual ~Piece() {}

    bool canMove(int dx, int dy) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (shape[i][j] != ' ') {
                    int tx = x + j + dx;
                    int ty = y + i + dy;
                    if (tx < 1 || tx >= W - 1 || ty >= H - 1) return false;
                    if (ty >= 0 && board[ty][tx] != ' ') return false;
                }
            }
        }
        return true;
    }

    virtual void rotate() {
        char temp[4][4];
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                temp[j][3 - i] = shape[i][j];

        bool ok = true;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (temp[i][j] != ' ') {
                    int tx = x + j;
                    int ty = y + i;
                    if (tx < 1 || tx >= W - 1 || ty >= H - 1 || (ty >= 0 && board[ty][tx] != ' ')) {
                        ok = false;
                        break;
                    }
                }
            }
            if (!ok) break;
        }

        if (ok) {
            for (int i = 0; i < 4; i++)
                for (int j = 0; j < 4; j++)
                    shape[i][j] = temp[i][j];
        }
    }
};

class PieceI : public Piece { public: PieceI() { colorCode = 11; shape[1][0] = 'I'; shape[1][1] = 'I'; shape[1][2] = 'I'; shape[1][3] = 'I'; } };
class PieceO : public Piece { public: PieceO() { colorCode = 14; shape[1][1] = 'O'; shape[1][2] = 'O'; shape[2][1] = 'O'; shape[2][2] = 'O'; } void rotate() override {} };
class PieceT : public Piece { public: PieceT() { colorCode = 13; shape[1][1] = 'T'; shape[2][0] = 'T'; shape[2][1] = 'T'; shape[2][2] = 'T'; } };
class PieceS : public Piece { public: PieceS() { colorCode = 10; shape[1][1] = 'S'; shape[1][2] = 'S'; shape[2][0] = 'S'; shape[2][1] = 'S'; } };
class PieceZ : public Piece { public: PieceZ() { colorCode = 12; shape[1][0] = 'Z'; shape[1][1] = 'Z'; shape[2][1] = 'Z'; shape[2][2] = 'Z'; } };
class PieceJ : public Piece { public: PieceJ() { colorCode = 9;  shape[1][0] = 'J'; shape[2][0] = 'J'; shape[2][1] = 'J'; shape[2][2] = 'J'; } };
class PieceL : public Piece { public: PieceL() { colorCode = 6;  shape[1][2] = 'L'; shape[2][0] = 'L'; shape[2][1] = 'L'; shape[2][2] = 'L'; } };

Piece* currentPiece = nullptr;
Piece* nextPiece = nullptr;

Piece* createPiece(int id) {
    switch (id) {
    case 0: return new PieceI();
    case 1: return new PieceO();
    case 2: return new PieceT();
    case 3: return new PieceS();
    case 4: return new PieceZ();
    case 5: return new PieceJ();
    case 6: return new PieceL();
    }
    return new PieceI();
}

int getBlockColor(char type) {
    switch (type) {
    case 'I': return 11;
    case 'O': return 14;
    case 'T': return 13;
    case 'S': return 10;
    case 'Z': return 12;
    case 'J': return 9;
    case 'L': return 6;
    case '#': return 8;
    default: return 0;
    }
}

void boardDelBlock() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (currentPiece->shape[i][j] != ' ') {
                int by = currentPiece->y + i;
                int bx = currentPiece->x + j;
                if (by >= 0 && by < H && bx >= 0 && bx < W) {
                    if (board[by][bx] == currentPiece->shape[i][j]) {
                        board[by][bx] = ' ';
                    }
                }
            }
        }
    }
}

void block2Board() {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (currentPiece->shape[i][j] != ' ') {
                int by = currentPiece->y + i;
                int bx = currentPiece->x + j;
                if (by >= 0 && by < H && bx >= 0 && bx < W)
                    board[by][bx] = currentPiece->shape[i][j];
            }
}

void initBoard() {
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if (i == H - 1 || j == 0 || j == W - 1)
                board[i][j] = '#';
            else
                board[i][j] = ' ';
        }
    }
}

void drawNextPiece() {
    int nextX = START_X + W * 2 + 5;
    int nextY = START_Y + 1;

    gotoxy(nextX, nextY - 1);
    setColor(15); cout << "NEXT:";

    // Clear area
    for (int i = 0; i < 4; i++) {
        gotoxy(nextX, nextY + i);
        cout << "        ";
    }

    if (nextPiece) {
        setColor(nextPiece->colorCode);
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (nextPiece->shape[i][j] != ' ') {
                    gotoxy(nextX + j * 2, nextY + i);
                    cout << "[]";
                }
            }
        }
    }
}

void drawUI() {
    int infoX = START_X + W * 2 + 5;

    setColor(15);
    gotoxy(infoX, START_Y + 6); cout << "SCORE:";
    setColor(14);
    gotoxy(infoX, START_Y + 7); cout << score;

    setColor(15);
    gotoxy(infoX, START_Y + 9); cout << "COMBO:";
    if (comboCount > 1) setColor(12); else setColor(7);
    gotoxy(infoX, START_Y + 10); cout << comboCount;

    setColor(8);
    gotoxy(infoX, START_Y + 13); cout << "CONTROLS:";
    gotoxy(infoX, START_Y + 14); cout << "A/D : Move";
    gotoxy(infoX, START_Y + 15); cout << "S   : Drop";
    gotoxy(infoX, START_Y + 16); cout << "W   : Rotate";
    gotoxy(infoX, START_Y + 17); cout << "P   : Pause";
    gotoxy(infoX, START_Y + 18); cout << "Q   : Quit";
}

void drawBoard() {
    for (int i = 0; i < H; i++) {
        gotoxy(START_X, START_Y + i);
        for (int j = 0; j < W; j++) {
            char cell = board[i][j];
            if (cell == '#') {
                setColor(8);
                if (i == H - 1) cout << "==";
                else cout << "||";
            }
            else if (cell != ' ') {
                setColor(getBlockColor(cell));
                cout << "[]";
            }
            else {
                setColor(0);
                cout << " .";
            }
        }
    }
}

void checkAndRemoveLines() {
    int linesClearedThisTurn = 0;

    int i = H - 2;
    while (i >= 0) {
        bool full = true;
        for (int j = 1; j <= W - 2; j++) {
            if (board[i][j] == ' ') {
                full = false;
                break;
            }
        }

        if (full) {
            linesClearedThisTurn++;
            for (int r = i; r > 0; r--) {
                for (int c = 1; c <= W - 2; c++) {
                    board[r][c] = board[r - 1][c];
                }
            }
            for (int c = 1; c <= W - 2; c++)
                board[0][c] = ' ';
            if (dropDelay > 50) dropDelay -= 5;
        }
        else {
            i--;
        }
    }

    if (linesClearedThisTurn > 0) {
        comboCount++;
        int baseScore = 0;
        switch (linesClearedThisTurn) {
        case 1: baseScore = 100; break;
        case 2: baseScore = 300; break;
        case 3: baseScore = 500; break;
        case 4: baseScore = 800; break;
        default: baseScore = 100 * linesClearedThisTurn;
        }
        int bonus = (comboCount - 1) * 50;
        if (bonus < 0) bonus = 0;
        score += baseScore + bonus;
    }
    else {
        comboCount = 0;
    }
}

int main()
{
    hideCursor();
    srand((unsigned)time(0));

    int choice = menu();
    if (choice == 5) return 0;

    if (choice == 2) dropDelay = 500;
    else if (choice == 4) dropDelay = 100;
    else dropDelay = 300;

    system("cls");
    initBoard();

    // Vẽ khung bao quanh, tự động co giãn theo W và H
    drawBorderBox(START_X - 1, START_Y - 1, W * 2 + 1, H);

    PlaySound(TEXT("music.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

    currentPiece = createPiece(rand() % 7);
    nextPiece = createPiece(rand() % 7);

    block2Board();

    while (true) {
        if (_kbhit()) {
            char c = _getch();
            if (c == 'p' || c == 'P') {
                isPaused = !isPaused;
            }

            if (!isPaused) {
                boardDelBlock();
                if ((c == 'a' || c == 'A') && currentPiece->canMove(-1, 0)) currentPiece->x--;
                if ((c == 'd' || c == 'D') && currentPiece->canMove(1, 0)) currentPiece->x++;
                if ((c == 's' || c == 'S') && currentPiece->canMove(0, 1)) currentPiece->y++;
                if ((c == 'w' || c == 'W')) currentPiece->rotate();
                block2Board();
            }

            if (c == 'q' || c == 'Q') break;
        }

        if (isPaused) {
            // Tự động tính toán tâm của bảng (bất kể kích thước)
            gotoxy(START_X + W - 4, START_Y + H / 2);
            setColor(BACKGROUND_RED | FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            cout << " PAUSED ";
            Sleep(100);
            continue;
        }

        boardDelBlock();
        if (currentPiece->canMove(0, 1)) {
            currentPiece->y++;
        }
        else {
            block2Board();
            checkAndRemoveLines();

            delete currentPiece;
            currentPiece = nextPiece;
            nextPiece = createPiece(rand() % 7);

            drawNextPiece();

            if (!currentPiece->canMove(0, 0)) {
                block2Board();
                drawBoard();

                // Tự động căn giữa chữ GAME OVER
                gotoxy(START_X + W - 5, START_Y + H / 2);
                setColor(BACKGROUND_RED | FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                cout << " GAME OVER ";

                gotoxy(START_X + W - 6, START_Y + H / 2 + 1);
                setColor(BACKGROUND_BLUE | FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                cout << " Score: " << score << " ";
                break;
            }
        }

        block2Board();
        drawBoard();
        drawUI();
        drawNextPiece();
        Sleep(dropDelay);
    }

    return 0;
}
