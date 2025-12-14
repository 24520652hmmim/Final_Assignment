#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>
#include <cstdlib>
using namespace std;

#define H 20
#define W 20

char board[H][W] = {};
int dropDelay = 200;    
void hideCursor() {
    CONSOLE_CURSOR_INFO ci;
    ci.dwSize = 1;
    ci.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ci);
}     
inline bool inPlayable(int tx, int ty)
{
    return (tx >= 1 && tx <= W - 2 && ty >= 0 && ty <= H - 2);
}
int menu() {
    while (true) {
        system("cls");
        cout << "====== TETRIS ======\n";
        cout << "1. Start Game\n";
        cout << "2. Speed: Slow\n";
        cout << "3. Speed: Normal\n";
        cout << "4. Speed: Fast\n";
        cout << "5. Exit\n";
        cout << "====================\n";
        cout << "Press 1-5";

        char c = _getch();
        if (c >= '1' && c <= '5') return c - '0';
    }
}
class Piece
{
public:
    char shape[4][4];
    int x, y;

    Piece()
    {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                shape[i][j] = ' ';
        x = W / 2 - 2;
        y = 0;
    }

    virtual ~Piece() {}

    bool canMove(int dx, int dy)
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (shape[i][j] != ' ')
                {
                    int tx = x + j + dx;
                    int ty = y + i + dy;

                    if (!inPlayable(tx, ty))
                        return false;

                    if (ty >= 0 && board[ty][tx] != ' ')
                        return false;
                }
            }
        }
        return true;
    }

    virtual void rotate()
    {
        char temp[4][4];
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                temp[j][3 - i] = shape[i][j];

        int kicks[] = {0, -1, 1, -2, 2};

        for (int k = 0; k < 5; k++)
        {
            int dx = kicks[k];
            bool ok = true;

            for (int i = 0; i < 4 && ok; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    if (temp[i][j] != ' ')
                    {
                        int tx = x + j + dx;
                        int ty = y + i;
                        if (!inPlayable(tx, ty))
                        {
                            ok = false;
                            break;
                        }
                        if (ty >= 0 && board[ty][tx] != ' ')
                        {
                            ok = false;
                            break;
                        }
                    }
                }
            }

            if (ok)
            {
                for (int i = 0; i < 4; i++)
                    for (int j = 0; j < 4; j++)
                        shape[i][j] = temp[i][j];
                x += dx;
                return;
            }
        }
    }
};

class PieceI : public Piece
{
public:
    PieceI()
    {
        shape[0][1] = 'I';
        shape[1][1] = 'I';
        shape[2][1] = 'I';
        shape[3][1] = 'I';
    }
};

class PieceO : public Piece
{
public:
    PieceO()
    {
        shape[1][1] = 'O';
        shape[1][2] = 'O';
        shape[2][1] = 'O';
        shape[2][2] = 'O';
    }
    void rotate() override {}
};

class PieceT : public Piece
{
public:
    PieceT()
    {
        shape[1][1] = 'T';
        shape[2][0] = 'T';
        shape[2][1] = 'T';
        shape[2][2] = 'T';
    }
};

class PieceS : public Piece
{
public:
    PieceS()
    {
        shape[1][1] = 'S';
        shape[1][2] = 'S';
        shape[2][0] = 'S';
        shape[2][1] = 'S';
    }
};

class PieceZ : public Piece
{
public:
    PieceZ()
    {
        shape[1][0] = 'Z';
        shape[1][1] = 'Z';
        shape[2][1] = 'Z';
        shape[2][2] = 'Z';
    }
};

class PieceJ : public Piece
{
public:
    PieceJ()
    {
        shape[1][0] = 'J';
        shape[2][0] = 'J';
        shape[2][1] = 'J';
        shape[2][2] = 'J';
    }
};

class PieceL : public Piece
{
public:
    PieceL()
    {
        shape[1][2] = 'L';
        shape[2][0] = 'L';
        shape[2][1] = 'L';
        shape[2][2] = 'L';
    }
};

Piece *currentPiece = nullptr;

Piece *createPiece(int id)
{
    switch (id)
    {
    case 0:
        return new PieceI();
    case 1:
        return new PieceO();
    case 2:
        return new PieceT();
    case 3:
        return new PieceS();
    case 4:
        return new PieceZ();
    case 5:
        return new PieceJ();
    case 6:
        return new PieceL();
    }
    return new PieceI();
}

int score = 0;
int delay = 500;

void gotoxy(int x, int y)
{
    COORD c = {(SHORT)x, (SHORT)y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void boardDelBlock()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (currentPiece->shape[i][j] != ' ')
            {
                int by = currentPiece->y + i;
                int bx = currentPiece->x + j;
                if (by >= 0 && by < H && bx >= 0 && bx < W)
                {
                    if (board[by][bx] == currentPiece->shape[i][j])
                    {
                        board[by][bx] = ' ';
                    }
                }
            }
        }
    }
}

void block2Board()
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (currentPiece->shape[i][j] != ' ')
            {
                int by = currentPiece->y + i;
                int bx = currentPiece->x + j;
                if (by >= 0 && by < H && bx >= 0 && bx < W)
                    board[by][bx] = currentPiece->shape[i][j];
            }
}

void initBoard()
{
    for (int i = 0; i < H; i++)
        for (int j = 0; j < W; j++)
            if ((i == H - 1) || (j == 0) || (j == W - 1))
                board[i][j] = '#';
            else
                board[i][j] = ' ';
}

void draw()
{
    gotoxy(0, 0);
    cout << "Score: " << score << "\n\n";
    for (int i = 0; i < H; i++, cout << endl)
    {
        for (int j = 0; j < W; j++)
        {
            if (board[i][j] == '#')
                cout << "##";
            else if (board[i][j] != ' ')
                cout << "[]";
            else
                cout << "  ";
        }
    }
    cout << "\nControls: A (Left), D (Right), S (Down), W (Rotate), Q (Quit)\n";
}

void removeLine()
{
    int i = H - 2;
    while (i >= 0)
    {
        bool full = true;
        for (int j = 1; j <= W - 2; j++)
        {
            if (board[i][j] == ' ')
            {
                full = false;
                break;
            }
        }

        if (full)
        {
            score += 100;
            if (delay > 50)
                delay -= 10;

            for (int r = i; r > 0; r--)
            {
                for (int c = 1; c <= W - 2; c++)
                {
                    board[r][c] = board[r - 1][c];
                }
            }

            for (int c = 1; c <= W - 2; c++)
                board[0][c] = ' ';
        }
        else
        {
            i--;
        }
    }
}

int main()
{
    
	srand(time(0));
    hideCursor();
    while (true) {
        int c = menu();
        if (c == 1) break;
        if (c == 2) dropDelay = 400;
        if (c == 3) dropDelay = 200;
        if (c == 4) dropDelay = 100;
        if (c == 5) return 0;
    }
    system("cls");
    initBoard();

    int b = rand() % 7;
    currentPiece = createPiece(b);

    block2Board();
    draw();

    clock_t lastTime = clock();

    while (1)
    {
        boardDelBlock();

        if (_kbhit())
        {
            char c = _getch();
            if ((c == 'a' || c == 'A') && currentPiece->canMove(-1, 0))
                currentPiece->x--;
            if ((c == 'd' || c == 'D') && currentPiece->canMove(1, 0))
                currentPiece->x++;
            if ((c == 's' || c == 'S') && currentPiece->canMove(0, 1))
                currentPiece->y++;
            if ((c == 'w' || c == 'W'))
                currentPiece->rotate();
            if ((c == 'q' || c == 'Q'))
                break;
        }

        if (currentPiece->canMove(0, 1))
{
    currentPiece->y++;
}
else
{
    block2Board();
    removeLine();

    delete currentPiece;
    b = rand() % 7;
    currentPiece = createPiece(b);

    if (!currentPiece->canMove(0, 0))
    {
        block2Board();
        draw();
        gotoxy(0, H + 3);
        cout << "\nGame Over! Final score: " << score << "\n";
        break;
    }
}


        block2Board();
        draw();
        Sleep(dropDelay);
    }
    return 0;
}
