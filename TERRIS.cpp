#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>
using namespace std;

#define H 20
#define W 15

char board[H][W] = {} ;
char blocks[][4][4] = {
    {{' ','I',' ',' '},
     {' ','I',' ',' '},
     {' ','I',' ',' '},
     {' ','I',' ',' '}},
    {{' ',' ',' ',' '},
     {' ','O','O',' '},
     {' ','O','O',' '},
     {' ',' ',' ',' '}},
    {{' ',' ',' ',' '},
     {' ','T',' ',' '},
     {'T','T','T',' '},
     {' ',' ',' ',' '}},
    {{' ',' ',' ',' '},
     {' ','S','S',' '},
     {'S','S',' ',' '},
     {' ',' ',' ',' '}},
    {{' ',' ',' ',' '},
     {'Z','Z',' ',' '},
     {' ','Z','Z',' '},
     {' ',' ',' ',' '}},
    {{' ',' ',' ',' '},
     {'J',' ',' ',' '},
     {'J','J','J',' '},
     {' ',' ',' ',' '}},
    {{' ',' ',' ',' '},
     {' ',' ','L',' '},
     {'L','L','L',' '},
     {' ',' ',' ',' '}}
};

int x = 4, y = 0, b = 0;
int score = 0;

void gotoxy(int x, int y) {
    COORD c = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void boardDelBlock(){
    for (int i = 0 ; i < 4 ; i++)
        for (int j = 0 ; j < 4 ; j++)
            if (blocks[b][i][j] != ' '){
                int by = y + i;
                int bx = x + j;
                if (by >= 0 && by < H && bx >= 0 && bx < W)
                    board[by][bx] = ' ';
            }
}

void block2Board(){
    for (int i = 0 ; i < 4 ; i++)
        for (int j = 0 ; j < 4 ; j++)
            if (blocks[b][i][j] != ' ' ){
                int by = y + i;
                int bx = x + j;
                if (by >= 0 && by < H && bx >= 0 && bx < W)
                    board[by][bx] = blocks[b][i][j];
            }
}

void initBoard(){
    for (int i = 0 ; i < H ; i++)
        for (int j = 0 ; j < W ; j++)
            if ((i==H-1) || (j==0) || (j == W-1)) board[i][j] = '#';
            else board[i][j] = ' ';
}

void draw(){
    gotoxy(0,0);
    cout << "Score: " << score << "\n\n";
    for (int i = 0 ; i < H ; i++, cout << endl){
        for (int j = 0 ; j < W ; j++){
            if (board[i][j] == '#')
                cout << "##";
            else if (board[i][j] != ' ')
                cout << "[]";
            else
                cout << "  ";
        }
    }
}

// Hàm xóa dòng d?y và d?y các dòng phía trên xu?ng
void removeLine() {
    int i = H - 2; // t? hàng trên cùng c?a dáy (H-1 là biên dáy)
    while (i >= 0) {
        bool full = true;
        for (int j = 1; j <= W - 2; j++) {
            if (board[i][j] == ' ') { full = false; break; }
        }

        if (full) {
            // tang di?m (ví d? 100 cho 1 hàng)
            score += 100;

            // d?y t?t c? hàng phía trên xu?ng 1
            for (int r = i; r > 0; r--) {
                for (int c = 1; c <= W - 2; c++) {
                    board[r][c] = board[r-1][c];
                }
            }
            // làm r?ng hàng trên cùng (ph?n trong biên)
            for (int c = 1; c <= W - 2; c++) board[0][c] = ' ';
            // không gi?m i d? ki?m tra l?i hàng m?i t?i v? trí i
        } else {
            i--;
        }
    }
}

bool canMove(int dx, int dy){
    for (int i = 0 ; i < 4 ; i++)
        for (int j = 0 ; j < 4 ; j++)
            if (blocks[b][i][j] != ' '){
                int tx = x + j + dx;
                int ty = y + i + dy;
                // ki?m tra ranh gi?i trong vùng choi (c?t 1..W-2, hàng 0..H-2)
                if (tx < 1 || tx >= W-1 || ty >= H-1) return false;
                if (ty >= 0 && board[ty][tx] != ' ') return false;
            }
    return true;
}

int main()
{
    srand((unsigned)time(0));
    b = rand() % 7;
    x = 4; y = 0;
    system("cls");
    initBoard();
    block2Board();
    draw();

    while (1){
        boardDelBlock();

        if (kbhit()){
            char c = getch();
            if ((c=='a' || c=='A') && canMove(-1,0)) x--;
            if ((c=='d' || c=='D') && canMove(1,0)) x++;
            if ((c=='x' || c=='X') && canMove(0,1)) y++;
            if ((c=='q' || c=='Q')) break;
        }

        // roi t? d?ng
        if (canMove(0,1)) {
            y++;
        } else {
            // dóng block vào board
            block2Board();
            // ki?m tra và xóa dòng d?y
            removeLine();
            // sinh block m?i ? v? trí ban d?u
            b = rand() % 7;
            x = 4;
            y = 0;
            // n?u block m?i không th? n?m t?i v? trí b?t d?u -> game over
            if (!canMove(0,0)) {
                gotoxy(0, H + 3);
                cout << "\nGame Over! Final score: " << score << "\n";
                break;
            }
        }

        block2Board();
        draw();
        Sleep(200);
    }
    return 0;
}

