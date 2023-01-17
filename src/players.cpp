#include "players.h"
#include "game.h"
#include <conio.h>
extern vector<pair<int, int>>checked_coordinates;

extern PLAYERS CurrentPlayer;
extern int points_1;
extern int points_2;

extern P* p1;
extern P* p2;
extern P* AI;

static int p_hit[2] = { 0,0 };
static int c_hit = 0;

static SHIPS hit_ship_p[2] = { EMPTY,EMPTY };
static SHIPS hit_ship_c;

static int good_x = 0;
static int good_y = 0;

static DIRECTION direction;

bool check(int x_p, int y_p, int x_k, int y_k, int k, char** board)
{
    if (x_p == x_k)
    {
        if (y_p < y_k) {
            for (int i = y_p; i < y_p + k; i++) {
                if (board[x_p][i] == 'X' || board[x_p][i] == 'O') {
                    return false;
                }
            }
            if (y_k - 1 >= 0) {
                if (x_k - 1 >= 0) {
                    if(board[x_p - 1][y_p - 1] == 'X' )
                        return false;
                }
                if (x_p + 1 < 10) {
                    if(board[x_p + 1][y_p - 1] == 'X' )
                        return false;
                }
                if(board[x_p][y_p - 1] == 'X')
                    return false;
            }
            if (y_p + k < 10) {
                if (x_p - 1 >= 0) {
                    if(board[x_p - 1][y_p + k] == 'X' )
                        return false;
                }
                if (x_p + 1 < 10) {
                    if(board[x_p + 1][y_p + k] == 'X' )
                        return false;
                }
                if(board[x_p][y_p + k] == 'X')
                    return false;
            }
            for (int i = 0; i < k; i++) {
                if (x_p - 1 >= 0) {
                    if (board[x_p - 1][y_p + i] == 'X')
                        return false;
                }
                if (x_p + 1 < 10) {
                    if (board[x_p + 1][y_p + i] == 'X')
                        return false;
                }
            }
        }
        else {
            for (int i = y_k; i < y_k + k; i++) {
                if (board[x_k][i] == 'X' || board[x_k][i]=='O') {
                    return false;
                }
            }
            if (y_k - 1 >= 0) {
                if (x_k - 1 >= 0) {
                    if(board[x_k - 1][y_k - 1] == 'X')
                        return false;
                }
                if (x_k + 1 < 10) {
                    if(board[x_k + 1][y_k - 1] == 'X')
                        return false;
                }
                if (board[x_k][y_k - 1] == 'X')
                        return false;
            }
            if (y_k + k < 10) {
                if (x_k - 1 >= 0) {
                    if(board[x_k - 1][y_k + k] == 'X' )
                        return false;
                }
                if (x_p + 1 < 10) {
                    if(board[x_k + 1][y_k + k] == 'X' )
                        return false;
                }
                if(board[x_k][y_k + k] == 'X' )
                    return false;
            }
            for (int i = 0; i < k; i++) {
                if (x_k - 1 >= 0) {
                    if(board[x_k - 1][y_k + i] == 'X')
                        return false;
                }
                if (x_k + 1 < 10) {
                    if(board[x_k + 1][y_k + i] == 'X' )
                        return false;
                }
            }
        }
    }
    if (y_p == y_k)
    {
        if (x_p < x_k) {
            for (int i = x_p; i < x_p + k; i++) {
                if (board[i][y_p] == 'X' || board[i][y_p] == 'O') {
                    return false;
                }
            }
                if (x_p - 1 >= 0)
                {
                    if(board[x_p - 1][y_p]=='X' )
                        return false;
                    if (y_p - 1 >= 0) {
                        if(board[x_p - 1][y_p] == 'X' )
                            return false;
                    }
                    if (y_p + 1 < 10) {
                        if(board[x_p - 1][y_p + 1] == 'X' )
                            return false;
                    }
                }
                for (int i = 0; i < k; i++) {
                    if (y_p - 1 >= 0) {
                        if(board[x_p + k][y_p - 1] == 'X')
                            return false;
                    }
                    if (y_p + 1 < 10) {
                        if(board[x_p + k][y_p + 1] == 'X' )
                            return false;
                    }
                }
                if (x_p + k < 10) {
                    if (y_p - 1 >= 0) {
                        if (board[x_p + k][y_p - 1] == 'X' )
                            return false;
                    }
                    if (y_p + 1 < 10) {
                        if (board[x_p + k][y_p + 1] == 'X' )
                            return false;
                    }
                    if (board[x_p + k][y_p] == 'X')
                        return false;
                }
        }
        else {
            for (int i = x_k; i < x_k + k; i++) {
                if (board[i][y_k] == 'X' || board[i][y_k] == 'O') {
                    return false;
                }
            }
            if (x_k - 1 >= 0)
            {
                if(board[x_k - 1][y_k] == 'X')
                    return false;
                if (y_k - 1 >= 0) {
                    if(board[x_k - 1][y_k] == 'X')
                        return false;
                }
                if (y_k + 1 < 10) {
                    if(board[x_k - 1][y_k + 1] == 'X')
                        return false;
                }
            }
            for (int i = 0; i < k; i++) {
                if (y_k - 1 >= 0) {
                    if(board[x_k + i][y_k - 1] == 'X')
                        return false;
                }
                if (y_k + 1 < 10) {
                    if(board[x_k + i][y_k + 1] == 'X')
                        return false;
                }
            }
            if (x_k + k < 10) {
                if (y_k - 1 >= 0) {
                    if (board[x_k + k][y_k - 1] == 'X')
                        return false;
                }
                if (y_p + 1 < 10) {
                    if (board[x_k + k][y_k + 1] == 'X')
                        return false;
                }
                if (board[x_k + k][y_k] == 'X')
                    return false;
            }
        }
    }
    return true;
}
void autoset(P* player,int length,SHIPS s)
{
    int x_begin, y_begin;
    int x_end, y_end;
    DIRECTION k;
    bool t = false;

    while (!t)
    {
        x_begin = rand() % 10 + 1;
        y_begin = rand() % 10 + 1;
        k = ((rand() % 4 + 1) % 2 == 0 ? VERTICAL : HORIZONTAL);

        x_begin--; y_begin--;
        if (k == HORIZONTAL) {
            if (x_begin + length < 10)
            {
                if (check(x_begin, y_begin, x_begin + length, y_begin, length, player->board)) {
                    x_end = x_begin + length;
                    y_end = y_begin;
                    for (int i = x_begin; i < x_begin + length; i++) {
                        player->board[i][y_begin] = 'X';
                        player->board_s[i][y_begin] = s;
                    }

                    if (x_begin - 1 >= 0)
                    {
                        player->board[x_begin - 1][y_begin] = 'O';
                        if (y_begin - 1 >= 0) {
                            player->board[x_begin - 1][y_begin] = 'O';
                        }
                        if (y_begin + 1 < 10) {
                            player->board[x_begin - 1][y_begin + 1] = 'O';
                        }
                    }
                    for (int i = 0; i < length; i++) {
                        if (y_begin - 1 >= 0) {
                            player->board[x_begin + i][y_begin - 1] = 'O';
                        }
                        if (y_begin + 1 < 10) {
                            player->board[x_begin + i][y_begin + 1] = 'O';
                        }
                    }
                    if (x_begin + length < 10) {
                        if (y_begin - 1 >= 0) {
                            player->board[x_begin + length][y_begin - 1] = 'O';
                        }
                        if (y_begin + 1 < 10) {
                            player->board[x_begin + length][y_begin + 1] = 'O';
                        }
                        player->board[x_begin + length][y_begin] = 'O';
                    }
                    {

                        t = true;
                    }
                }
            }
            else if (x_begin + length >= 10 && x_begin - length >= 0)
            {
                if (check(x_begin, y_begin, x_begin - length, y_begin, length, player->board)) {
                    x_end = x_begin - length;
                    y_end = y_begin;
                    for (int i = x_end; i < x_end + length; i++) {
                        player->board[i][y_end] = 'X';
                        player->board_s[i][y_end] = s;
                    }

                    if (x_end - 1 >= 0)
                    {
                        player->board[x_end - 1][y_end] = 'O';
                        if (y_end - 1 >= 0) {
                            player->board[x_end - 1][y_end] = 'O';
                        }
                        if (y_end + 1 < 10) {
                            player->board[x_end - 1][y_end + 1] = 'O';
                        }
                    }
                    for (int i = 0; i < length; i++) {
                        if (y_end - 1 >= 0) {
                            player->board[x_end + i][y_end - 1] = 'O';
                        }
                        if (y_end + 1 < 10) {
                            player->board[x_end + i][y_end + 1] = 'O';
                        }
                    }
                    if (x_end + length < 10) {
                        if (y_end - 1 >= 0) {
                            player->board[x_end + length][y_end - 1] = 'O';
                        }
                        if (y_begin + 1 < 10) {
                            player->board[x_end + length][y_end + 1] = 'O';
                        }
                        player->board[x_end + length][y_end] = 'O';
                    }
                    t = true;
                }
            }
        }

        else if (k == VERTICAL) {
            if (y_begin + length < 10) {
                if (check(x_begin, y_begin, x_begin, y_begin + length, length, player->board)) {
                    x_end = x_begin;
                    y_end = y_begin + length;
                    for (int i = y_begin; i < y_begin + length; i++) {
                        player->board[x_begin][i] = 'X';
                        player->board_s[x_begin][i] = s;
                    }
                    if (y_begin - 1 >= 0) {
                        if (x_begin - 1 >= 0) {
                            player->board[x_begin - 1][y_begin - 1] = 'O';
                        }
                        if (x_begin + 1 < 10) {
                            player->board[x_begin + 1][y_begin - 1] = 'O';
                        }
                        player->board[x_begin][y_begin - 1] = 'O';
                    }
                    if (y_begin + length < 10) {
                        if (x_begin - 1 >= 0) {
                            player->board[x_begin - 1][y_begin + length] = 'O';
                        }
                        if (x_begin + 1 < 10) {
                            player->board[x_begin + 1][y_begin + length] = 'O';
                        }
                        player->board[x_begin][y_begin + length] = 'O';
                    }
                    for (int i = 0; i < length; i++) {
                        if (x_begin - 1 >= 0) {
                            player->board[x_begin - 1][y_begin + i] = 'O';
                        }
                        if (x_begin + 1 < 10) {
                            player->board[x_begin + 1][y_begin + i] = 'O';
                        }
                    }

                    t = true;
                }
            }
            else if (y_begin + length >= 10 && y_begin - length >= 0) {
                if (check(x_begin, y_begin, x_begin, y_begin - length, length, player->board)) {
                    x_end = x_begin;
                    y_end = y_begin - length;
                    for (int i = y_end; i < y_end + length; i++) {
                        player->board[x_end][i] = 'X';
                        player->board_s[x_end][i] = s;
                    }
                    if (y_end - 1 >= 0) {
                        if (x_end - 1 >= 0) {
                            player->board[x_end - 1][y_end - 1] = 'O';
                        }
                        if (x_end + 1 < 10) {
                            player->board[x_end + 1][y_end - 1] = 'O';
                        }
                        player->board[x_end][y_end - 1] = 'O';
                    }
                    if (y_end + length < 10) {
                        if (x_end - 1 >= 0) {
                            player->board[x_end - 1][y_end + length] = 'O';
                        }
                        if (x_begin + 1 < 10) {
                            player->board[x_end + 1][y_end + length] = 'O';
                        }
                        player->board[x_end][y_end + length] = 'O';
                    }
                    for (int i = 0; i < length; i++) {
                        if (x_end - 1 >= 0) {
                            player->board[x_end - 1][y_end + i] = 'O';
                        }
                        if (x_end + 1 < 10) {
                            player->board[x_end + 1][y_end + i] = 'O';
                        }
                    }
                    t = true;
                }
            }
        }
    }
}
bool if_checked(int x, int y)
{
    for (int i = 0; i < checked_coordinates.size(); i++)
    {
        if (x == checked_coordinates[i].first && y == checked_coordinates[i].second)
            return true;
    }
    return false;
}
Player::Player(string n)
{
    nick = n;
    points = 0;
}
Player::Player()
{
    nick = "Nickname";
    points = 0;
}
Player::~Player()
{
    for (int i = 0; i < 10; i++)
    {
        delete[] board[i];
        delete[] board_to_check[i];
        delete[] board_s[i];
    }
    delete[] board;
    delete[] board_to_check;
    delete[] board_s;
}
void Player::operator++()
{
    points++;
}
void Player::SetBoard()
{
    board = new char* [SIZE];
    board_to_check = new char* [SIZE];
    board_s = new SHIPS * [SIZE];

    for (int i = 0; i < SIZE; i++)
    {
        board[i] = new char[SIZE];
        board_to_check[i] = new char[SIZE];
        board_s[i] = new SHIPS[SIZE];
    }

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            board[i][j] = '?';
            board_to_check[i][j] = '?';
            board_s[i][j] = EMPTY;
        }
    }
}
void Player::SetShip(int length,SHIPS s)
{
    system("cls");
    cout << "The ships are placed by: " << this->printName() << endl;
    for (int i = 0; i < 10; i++)
        cout << i + 1 << " ";
    cout << endl << endl;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            cout << board[i][j] << " ";
        }
        cout << " " << i + 1 << endl;
    }
    cout << endl;
    bool t = false;
    int row_begin, column_begin;
    int row_end, column_end;
    switch (s)
    {
        case FOUR:
        {
            cout << "Set up a four-masted ship" << endl;
            while (!t) {
                cout << "Enter the coordinates of the starting point: ";
                try {
                    cin >> row_begin >> column_begin;
                    if (row_begin <= 0 || column_begin <= 0 || row_begin >= 11 || column_begin >= 11) {
                        Exceptions<ERRORS>exception(ER_FIELD);
                        throw exception;
                    }
                    else if (row_begin - int(row_begin) != 0 || column_begin - int(column_begin) != 0) {
                        Exceptions<ERRORS>exception(ER_NUMS);
                        throw exception;
                    }
                    else
                        t = true;
                }
                catch(Exceptions<ERRORS>e) {
                    Exceptions<ERRORS>::manageException(reinterpret_cast<ERRORS &>(e));
                }
            }
            t = false;
            while (!t)
            {
                cout << "Enter the coordinates of the ending point(remember that the point needs to be four units away vertically or horizontally): ";
                try {
                    cin >> row_end >> column_end;
                    if (row_begin <= 0 || column_begin <= 0 || row_begin >= 11 || column_begin >= 11) {
                        Exceptions<ERRORS>exception(ER_FIELD);
                        throw exception;
                    }
                    else if (row_begin - int(row_begin) != 0 || column_begin - int(column_begin) != 0) {
                        Exceptions<ERRORS>exception(ER_NUMS);
                        throw exception;
                    }
                    else if (row_begin != row_end && column_begin != column_end) {
                        Exceptions<ERRORS>exception(ER_BAD_PLACEMENT);
                        throw exception;
                    }
                    else if (row_begin == row_end && abs(column_end - column_begin) + 1 != 4) {
                        Exceptions<ERRORS>exception(ER_BAD_PLACEMENT);
                        throw exception;
                    }
                    else if (column_begin == column_end && abs(row_end - row_begin) + 1 != 4) {
                        Exceptions<ERRORS>exception(ER_FIELD);
                        throw exception;
                    }
                    else
                        t = true;
                }
                catch(Exceptions<ERRORS>e) {
                    Exceptions<ERRORS>::manageException(reinterpret_cast<ERRORS &>(e));
                }
            }
            row_begin--; row_end--; column_begin--; column_end--;
            if (row_begin == row_end)
            {
                if (column_begin < column_end) {
                    for (int i = column_begin; i < column_begin + 4; i++) {
                        board[row_begin][i] = 'X';
                        board_s[row_begin][i] = FOUR;
                    }
                    if (row_begin - 1 >= 0) {
                        board[row_begin - 1][column_begin] = 'O';
                        board[row_begin - 1][column_begin + 1] = 'O';
                        board[row_begin - 1][column_begin + 2] = 'O';
                        board[row_begin - 1][column_begin + 3] = 'O';
                        if (column_begin - 1 >= 0) {
                            board[row_begin - 1][column_begin - 1] = 'O';
                        }
                        if (column_begin + 4 < 10) {
                            board[row_begin - 1][column_begin + 4] = 'O';
                        }
                    }
                    if (column_begin - 1 >= 0) {
                        board[row_begin][column_begin - 1] = 'O';
                    }
                    if (column_begin + 4 < 10) {
                        board[row_begin][column_begin + 4] = 'O';
                    }
                    if (row_begin + 1 < 10) {
                        board[row_begin + 1][column_begin] = 'O';
                        board[row_begin + 1][column_begin + 1] = 'O';
                        board[row_begin + 1][column_begin + 2] = 'O';
                        board[row_begin + 1][column_begin + 3] = 'O';
                        if (column_begin - 1 >= 0) {
                            board[row_begin + 1][column_begin - 1] = 'O';
                        }
                        if (column_begin + 4 < 10) {
                            board[row_begin + 1][column_begin + 4] = 'O';
                        }
                    }
                }
                else {
                    for (int i = column_end; i < column_end + 4; i++) {
                        board[row_end][i] = 'X';
                        board_s[row_end][i] = FOUR;
                    }
                    if (row_end - 1 >= 0) {
                        board[row_end - 1][column_end] = 'O';
                        board[row_end - 1][column_end + 1] = 'O';
                        board[row_end - 1][column_end + 2] = 'O';
                        board[row_end - 1][column_end + 3] = 'O';
                        if (column_end - 1 >= 0) {
                            board[row_end - 1][column_end - 1] = 'O';
                        }
                        if (column_end + 4 < 10) {
                            board[row_end - 1][column_end + 4] = 'O';
                        }
                    }
                    if (column_end - 1 >= 0) {
                        board[row_end][column_end - 1] = 'O';
                    }
                    if (column_end + 4 < 10) {
                        board[row_end][column_end + 4] = 'O';
                    }
                    if (row_end + 1 < 10) {
                        board[row_end + 1][column_end] = 'O';
                        board[row_end + 1][column_end + 1] = 'O';
                        board[row_end + 1][column_end + 2] = 'O';
                        board[row_end + 1][column_end + 3] = 'O';
                        if (column_end - 1 >= 0) {
                            board[row_end + 1][column_end - 1] = 'O';
                        }
                        if (column_end + 4 < 10) {
                            board[row_end + 1][column_end + 4] = 'O';
                        }
                    }

                }
            }
            if (column_begin == column_end)
            {
                if (row_begin < row_end) {
                    for (int i = row_begin; i < row_begin + 4; i++) {
                        board[i][column_begin] = 'X';
                        board_s[i][column_begin] = FOUR;
                    }

                    if (row_begin - 1 >= 0) {
                        board[row_begin - 1][column_begin] = 'O';
                        if (column_begin - 1 >= 0) {
                            board[row_begin - 1][column_begin - 1] = 'O';
                        }
                        if (column_begin + 1 < 10) {
                            board[row_begin - 1][column_begin + 1] = 'O';
                        }
                    }
                    if (column_begin - 1 >= 0) {
                        board[row_begin][column_begin - 1] = 'O';
                        board[row_begin + 1][column_begin - 1] = 'O';
                        board[row_begin + 2][column_begin - 1] = 'O';
                        board[row_begin + 3][column_begin - 1] = 'O';
                        if (row_begin + 4 < 10) {
                            board[row_begin + 4][column_begin - 1] = 'O';
                        }
                    }
                    if (column_begin + 1 < 10) {
                        board[row_begin][column_begin + 1] = 'O';
                        board[row_begin + 1][column_begin + 1] = 'O';
                        board[row_begin + 2][column_begin + 1] = 'O';
                        board[row_begin + 3][column_begin + 1] = 'O';
                        if (row_begin + 4 < 10) {
                            board[row_begin + 4][column_begin + 1] = 'O';
                        }
                    }
                    if (row_begin + 4 < 10) {
                        board[row_begin + 4][column_begin] = 'O';
                    }

                }
                else {
                    for (int i = row_end; i < row_end + 4; i++) {
                        board[i][column_end] = 'X';
                        board_s[i][column_end] = FOUR;
                    }
                    if (row_end - 1 >= 0) {
                        board[row_end - 1][column_end] = 'O';
                        if (column_end - 1 >= 0) {
                            board[row_end - 1][column_end - 1] = 'O';
                        }
                        if (column_end + 1 < 10) {
                            board[row_end - 1][column_end + 1] = 'O';
                        }
                    }
                    if (column_end - 1 >= 0) {
                        board[row_end][column_end - 1] = 'O';
                        board[row_end + 1][column_end - 1] = 'O';
                        board[row_end + 2][column_end - 1] = 'O';
                        board[row_end + 3][column_end - 1] = 'O';
                        if (row_end + 4 < 10) {
                            board[row_end + 4][column_end - 1] = 'O';
                        }
                    }
                    if (column_end + 1 < 10) {
                        board[row_end][column_end + 1] = 'O';
                        board[row_end + 1][column_end + 1] = 'O';
                        board[row_end + 2][column_end + 1] = 'O';
                        board[row_end + 3][column_end + 1] = 'O';
                        if (row_end + 4 < 10) {
                            board[row_end + 4][column_end + 1] = 'O';
                        }
                    }
                    if (row_end + 4 < 10) {
                        board[row_end + 4][column_end] = 'O';
                    }

                }
            }
        }break;
        case THREE:
        {
            cout << "Set up a three-masted ship" << endl;
            while (!t) {
                cout << "Enter the coordinates of the starting point: ";
                try {
                    cin >> row_begin >> column_begin;
                    if (row_begin <= 0 || column_begin <= 0 || row_begin >= 11 || column_begin >= 11) {
                        Exceptions<ERRORS>exception(ER_FIELD);
                        throw exception;
                    }
                    else if (board[row_begin - 1][column_begin - 1] != '?') {
                        Exceptions<ERRORS>exception(ER_NR);
                        throw exception;
                    }
                    else if (row_begin - int(row_begin) != 0 || column_begin - int(column_begin) != 0) {
                        Exceptions<ERRORS>exception(ER_NUMS);
                        throw exception;
                    }
                    else if (board[row_begin - 1][column_begin - 1] != '?') {
                        Exceptions<ERRORS>exception(ER_NR);
                        throw exception;
                    }
                    else
                        t = true;
                }
                catch(Exceptions<ERRORS>e) {
                    Exceptions<ERRORS>::manageException(reinterpret_cast<ERRORS &>(e));
                }
            }
            t = false;
            while (!t) {
                cout << "Enter the coordinates of the ending point(remember that the point needs to be three units away vertically or horizontally): ";
                try {
                    cin >> row_end >> column_end;
                    if (row_end <= 0 || column_end <= 0 || row_end >= 11 || column_end >= 11) {
                        Exceptions<ERRORS>exception(ER_FIELD);
                        throw exception;
                    } else if (row_end - int(row_end) != 0 || column_end - int(column_end) != 0) {
                        Exceptions<ERRORS>exception(ER_NUMS);
                        throw exception;
                    } else if (row_begin != row_end && column_begin != column_end) {
                        Exceptions<ERRORS>exception(ER_BAD_PLACEMENT);
                        throw exception;
                    } else if (row_begin == row_end && abs(column_end - column_begin) + 1 != 3) {
                        Exceptions<ERRORS>exception(ER_BAD_PLACEMENT);
                        throw exception;
                    } else if (column_begin == column_end && abs(row_end - row_begin) + 1 != 3) {
                        Exceptions<ERRORS>exception(ER_BAD_PLACEMENT);
                        throw exception;
                    } else if (!check(row_begin - 1, column_begin - 1, row_end - 1, column_end - 1, 3, this->board)) {
                        Exceptions<ERRORS>exception(ER_NR);
                        throw exception;
                    } else
                        t = true;
                }
                catch(Exceptions<ERRORS>e) {
                    Exceptions<ERRORS>::manageException(reinterpret_cast<ERRORS &>(e));
                }
            }
            row_begin--; column_begin--; row_end--; column_end--;
            if (row_begin == row_end)
            {
                if (column_begin < column_end) {
                    for (int i = column_begin; i < column_begin + 3; i++) {
                        board[row_begin][i] = 'X';
                        board_s[row_begin][i] = THREE;
                    }

                    if (row_begin - 1 >= 0) {
                        board[row_begin - 1][column_begin] = 'O';
                        board[row_begin - 1][column_begin + 1] = 'O';
                        board[row_begin - 1][column_begin + 2] = 'O';
                        if (column_begin - 1 >= 0) {
                            board[row_begin - 1][column_begin - 1] = 'O';
                        }
                        if (column_begin + 3 < 10) {
                            board[row_begin - 1][column_begin + 3] = 'O';
                        }
                    }
                    if (column_begin - 1 >= 0) {
                        board[row_begin][column_begin - 1] = 'O';
                    }
                    if (column_begin + 3 < 10) {
                        board[row_begin][column_begin + 3] = 'O';
                    }
                    if (row_begin + 1 < 10) {
                        board[row_begin + 1][column_begin] = 'O';
                        board[row_begin + 1][column_begin + 1] = 'O';
                        board[row_begin + 1][column_begin + 2] = 'O';
                        if (column_begin - 1 >= 0) {
                            board[row_begin + 1][column_begin - 1] = 'O';
                        }
                        if (column_begin + 3 < 10) {
                            board[row_begin + 1][column_begin + 3] = 'O';
                        }
                    }
                }
                else {
                    for (int i = column_end; i < column_end + 3; i++) {
                        board[row_end][i] = 'X';
                        board_s[row_end][i] = THREE;
                    }

                    if (row_end - 1 >= 0) {
                        board[row_end - 1][column_end] = 'O';
                        board[row_end - 1][column_end + 1] = 'O';
                        board[row_end - 1][column_end + 2] = 'O';
                        if (column_begin - 1 >= 0) {
                            board[row_end - 1][column_end - 1] = 'O';
                        }
                        if (column_begin + 3 < 10) {
                            board[row_end - 1][column_end + 3] = 'O';
                        }
                    }
                    if (column_end - 1 >= 0) {
                        board[row_end][column_end - 1] = 'O';
                    }
                    if (column_end + 3 < 10) {
                        board[row_end][column_end + 3] = 'O';
                    }
                    if (row_end + 1 < 10) {
                        board[row_end + 1][column_end] = 'O';
                        board[row_end + 1][column_end + 1] = 'O';
                        board[row_end + 1][column_end + 2] = 'O';
                        if (column_end - 1 >= 0) {
                            board[row_end + 1][column_end - 1] = 'O';
                        }
                        if (column_end + 3 < 10) {
                            board[row_end + 1][column_end + 3] = 'O';
                        }
                    }

                }
            }
            if (column_begin == column_end)
            {
                if (row_begin < row_end) {
                    for (int i = row_begin; i < row_begin + 3; i++) {
                        board[i][column_begin] = 'X';
                        board_s[i][column_begin] = THREE;
                    }
                    if (row_begin - 1 >= 0) {
                        board[row_begin - 1][column_begin] = 'O';
                        if (column_begin - 1 >= 0) {
                            board[row_begin - 1][column_begin - 1] = 'O';
                        }
                        if (column_begin + 1 < 10) {
                            board[row_begin - 1][column_begin + 1] = 'O';
                        }
                    }
                    if (column_begin - 1 >= 0) {
                        board[row_begin][column_begin - 1] = 'O';
                        board[row_begin + 1][column_begin - 1] = 'O';
                        board[row_begin + 2][column_begin - 1] = 'O';
                        if (row_begin + 3 < 10) {
                            board[row_begin + 3][column_begin - 1] = 'O';
                        }
                    }
                    if (column_begin + 1 < 10) {
                        board[row_begin][column_begin + 1] = 'O';
                        board[row_begin + 1][column_begin + 1] = 'O';
                        board[row_begin + 2][column_begin + 1] = 'O';
                        if (row_begin + 3 < 10) {
                            board[row_begin + 3][column_begin + 1] = 'O';
                        }
                    }
                    if (row_begin + 3 < 10) {
                        board[row_begin + 3][column_begin] = 'O';
                    }
                }
                else {
                    for (int i = row_end; i < row_end + 3; i++) {
                        board[i][column_end] = 'X';
                        board_s[i][column_end] = THREE;
                    }

                    if (row_end - 1 >= 0) {
                        board[row_end - 1][column_end] = 'O';
                        if (column_end - 1 >= 0) {
                            board[row_end - 1][column_end - 1] = 'O';
                        }
                        if (column_end + 1 < 10) {
                            board[row_end - 1][column_end + 1] = 'O';
                        }
                    }
                    if (column_end - 1 >= 0) {
                        board[row_end][column_end - 1] = 'O';
                        board[row_end + 1][column_end - 1] = 'O';
                        board[row_end + 2][column_end - 1] = 'O';
                        if (row_end + 3 < 10) {
                            board[row_end + 3][column_end - 1] = 'O';
                        }
                    }
                    if (column_begin + 1 < 10) {
                        board[row_end][column_end + 1] = 'O';
                        board[row_end + 1][column_end + 1] = 'O';
                        board[row_end + 2][column_end + 1] = 'O';
                        if (row_end + 3 < 10) {
                            board[row_end + 3][column_end + 1] = 'O';
                        }
                    }
                    if (row_end + 3 < 10) {
                        board[row_end + 3][column_end] = 'O';
                    }

                }
            }
        }break;
        case TWO:
        {
            cout << "Set up a two-masted ship" << endl;
            while (!t) {
                cout << "Enter the coordinates of the starting point: ";
                try {
                    cin >> row_begin >> column_begin;
                    if (row_begin <= 0 || column_begin <= 0 || row_begin >= 11 || column_begin >= 11) {
                        Exceptions<ERRORS>exception(ER_FIELD);
                        throw exception;
                    }
                    else if (board[row_begin - 1][column_begin - 1] != '?') {
                        Exceptions<ERRORS>exception(ER_NR);
                        throw exception;
                    }
                    else if (row_begin - int(row_begin) != 0 || column_begin - int(column_begin) != 0) {
                        Exceptions<ERRORS>exception(ER_NUMS);
                        throw exception;
                    }
                    else if (board[row_begin - 1][column_begin - 1] != '?') {
                        Exceptions<ERRORS>exception(ER_NR);
                        throw exception;
                    }
                    else
                        t = true;
                }
                catch(Exceptions<ERRORS>e) {
                    Exceptions<ERRORS>::manageException(reinterpret_cast<ERRORS &>(e));
                }
            }
            t = false;
            while (!t)
            {
                cout << "Enter the coordinates of the ending point(remember that the point needs to be two units away vertically or horizontally): ";
                try {
                    cin >> row_end >> column_end;
                    if (row_end <= 0 || column_end <= 0 || row_end >= 11 || column_end >= 11) {
                        Exceptions<ERRORS>exception(ER_FIELD);
                        throw exception;
                    }
                    else if (row_end - int(row_end) != 0 || column_end - int(column_end) != 0) {
                        Exceptions<ERRORS>exception(ER_NUMS);
                        throw exception;
                    }
                    else if (row_begin != row_end && column_begin != column_end) {
                        Exceptions<ERRORS>exception(ER_BAD_PLACEMENT);
                        throw exception;
                    }
                    else if (row_begin == row_end && abs(column_end - column_begin) + 1 != 2) {
                        Exceptions<ERRORS>exception(ER_BAD_PLACEMENT);
                        throw exception;
                    }
                    else if (column_begin == column_end && abs(row_end - row_begin) + 1 != 2) {
                        Exceptions<ERRORS>exception(ER_BAD_PLACEMENT);
                        throw exception;
                    }
                    else if (!check(row_begin - 1, column_begin - 1, row_end - 1, column_end - 1, 2, this->board)) {
                        Exceptions<ERRORS>exception(ER_NR);
                        throw exception;
                    }
                    else
                        t = true;
                }
                catch(Exceptions<ERRORS>e) {
                    Exceptions<ERRORS>::manageException(reinterpret_cast<ERRORS &>(e));
                }
            }
            row_begin--; column_begin--; row_end--; column_end--;
            if (row_begin == row_end)
            {
                if (column_begin < column_end) {
                    for (int i = column_begin; i < column_begin + 2; i++) {
                        board[row_begin][i] = 'X';
                        board_s[row_begin][i] = TWO;
                    }

                    if (row_begin - 1 >= 0 && column_begin - 1 >= 0) {
                        board[row_begin - 1][column_begin - 1] = 'O';
                    }
                    if (row_begin - 1 >= 0) {
                        board[row_begin - 1][column_begin] = 'O';
                        board[row_begin - 1][column_begin + 1] = 'O';
                    }
                    if (row_begin - 1 >= 0 && column_begin + 2 < 10) {
                        board[row_begin - 1][column_begin + 2] = 'O';
                    }

                    if (column_begin - 1 >= 0) {
                        board[row_begin][column_begin - 1] = 'O';
                    }
                    if (column_begin + 2 < 10) {
                        board[row_begin][column_begin + 2] = 'O';
                    }

                    if (row_begin + 1 < 10 && column_begin - 1 >= 0) {
                        board[row_begin + 1][column_begin - 1] = 'O';
                    }
                    if (row_begin + 1 < 10) {
                        board[row_begin + 1][column_begin] = 'O';
                        board[row_begin + 1][column_begin + 1] = 'O';
                    }
                    if (row_begin + 1 < 10 && column_begin + 2 < 10) {
                        board[row_begin + 1][column_begin + 2] = 'O';
                    }
                }
                else {
                    for (int i = column_end; i < column_end + 2; i++) {
                        board[row_end][i] = 'X';
                        board_s[row_end][i] = TWO;
                    }

                    if (row_end - 1 >= 0 && column_end - 1 >= 0) {
                        board[row_end - 1][column_end - 1] = 'O';
                    }
                    if (row_begin - 1 >= 0) {
                        board[row_end - 1][column_end] = 'O';
                        board[row_end - 1][column_end + 1] = 'O';
                    }
                    if (row_end - 1 >= 0 && column_end + 2 < 10) {
                        board[row_end - 1][column_end + 2] = 'O';
                    }

                    if (column_end - 1 >= 0) {
                        board[row_end][column_end - 1] = 'O';
                    }
                    if (column_end + 2 < 10) {
                        board[row_end][column_end + 2] = 'O';
                    }

                    if (row_end + 1 < 10 && column_end - 1 >= 0) {
                        board[row_end + 1][column_end - 1] = 'O';
                    }
                    if (row_end + 1 < 10) {
                        board[row_end + 1][column_end] = 'O';
                        board[row_end + 1][column_end + 1] = 'O';
                    }
                    if (row_end + 1 < 10 && column_end + 2 < 10) {
                        board[row_end + 1][column_end + 2] = 'O';
                    }

                }
            }
            if (column_begin == column_end)
            {
                if (row_begin < row_end) {
                    for (int i = row_begin; i < row_begin + 2; i++) {
                        board[i][column_begin] = 'X';
                        board_s[i][column_begin] = TWO;
                    }

                    if (row_begin - 1 >= 0) {
                        board[row_begin - 1][column_begin] = 'O';
                        if (column_begin - 1 >= 0) {
                            board[row_begin - 1][column_begin - 1] = 'O';
                        }
                        if (column_begin + 1 < 10) {
                            board[row_begin - 1][column_begin + 1] = 'O';
                        }
                    }
                    if (column_begin - 1 >= 0) {
                        board[row_begin][column_begin - 1] = 'O';
                        board[row_begin + 1][column_begin - 1] = 'O';
                        if (row_begin + 2 < 10) {
                            board[row_begin + 2][column_begin - 1] = 'O';
                        }
                    }
                    if (column_begin + 1 < 10) {
                        board[row_begin][column_begin + 1] = 'O';
                        board[row_begin + 1][column_begin + 1] = 'O';
                        if (row_begin + 2 < 10) {
                            board[row_begin + 2][column_begin + 1] = 'O';
                        }
                    }
                    if (row_begin + 2 < 10) {
                        board[row_begin + 2][column_begin] = 'O';
                    }
                }
                else {
                    for (int i = row_end; i < row_end + 2; i++) {
                        board[i][column_end] = 'X';
                        board_s[i][column_end] = TWO;
                    }
                    if (row_end - 1 >= 0) {
                        board[row_end - 1][column_end] = 'O';
                        if (column_end - 1 >= 0) {
                            board[row_end - 1][column_end - 1] = 'O';
                        }
                        if (column_end + 1 < 10) {
                            board[row_end - 1][column_end + 1] = 'O';
                        }
                    }
                    if (column_end - 1 >= 0) {
                        board[row_end][column_end - 1] = 'O';
                        board[row_end + 1][column_end - 1] = 'O';
                        if (row_end + 2 < 10) {
                            board[row_end + 2][column_end - 1] = 'O';
                        }
                    }
                    if (column_end + 1 < 10) {
                        board[row_end][column_end + 1] = 'O';
                        board[row_end + 1][column_end + 1] = 'O';
                        if (row_end + 2 < 10) {
                            board[row_end + 2][column_end + 1] = 'O';
                        }
                    }
                    if (row_end + 2 < 10) {
                        board[row_end + 2][column_end] = 'O';
                    }

                }
            }
        }break;
        case ONE:
        {
            cout << "Set up a single mast ship" << endl;
            while (!t)
            {
                cout << "Enter the coordinates of the ship: ";
                try {
                    cin >> row_begin >> column_begin;
                    if (row_begin <= 0 || column_begin <= 0 || row_begin >= 11 || column_begin >= 11) {
                        Exceptions<ERRORS>exception(ER_FIELD);
                        throw exception;
                    }
                    else if (board[row_begin - 1][column_begin - 1] != '?') {
                        Exceptions<ERRORS>exception(ER_NR);
                        throw exception;
                    }
                    else if (row_begin - int(row_begin) != 0 || column_begin - int(column_begin) != 0) {
                        Exceptions<ERRORS>exception(ER_NUMS);
                        throw exception;
                    }
                    else if (board[row_begin - 1][column_begin - 1] != '?') {
                        Exceptions<ERRORS>exception(ER_NR);
                        throw exception;
                    }
                    else
                        t = true;
                }
                catch(Exceptions<ERRORS>e) {
                    Exceptions<ERRORS>::manageException(reinterpret_cast<ERRORS &>(e));
                }
            }
            row_begin--; column_begin--;
            board[row_begin][column_begin] = 'X';
            board_s[row_begin][column_begin] = ONE;

            int i, j;
            i = row_begin - 1;
            j = column_begin - 1;
            if (i >= 0 && j >= 0) {
                board[i][j] = 'O';
            }
            j++;
            if (i >= 0 && j >= 0 && j < 10) {
                board[i][j] = 'O';
            }
            j++;
            if (i >= 0 && j >= 0 && j < 10) {
                board[i][j] = 'O';
            }
            i++;
            j = column_begin - 1;
            if (j >= 0) {
                board[i][j] = 'O';
            }
            j += 2;
            if (j >= 0 && j < 10) {
                board[i][j] = 'O';
            }
            i++;
            j = column_begin - 1;
            if (i < 10 && j >= 0) {
                board[i][j] = 'O';
            }
            j++;
            if (i < 10 && j < 10) {
                board[i][j] = 'O';
            }
            j++;
            if (i < 10 && j < 10) {
                board[i][j] = 'O';
            }
        }break;
    }
}
void Player::Move(char** board, char** board_to_check, SHIPS** board_s)
{
    int x, y;
    bool t = false;
    while (!t)
    {
        cout << "Enter the coordinates you want to check: ";
       try {
            cin >> x >> y;
            if (x <= 0 || x >= 11 || y <= 0 || y >= 11) {
                Exceptions<ERRORS>exception(ER_FIELD);
                throw exception;
            }
            else if (x - int(x) != 0 || y - int(y) != 0) {
                Exceptions<ERRORS>exception(ER_NUMS);
                throw exception;
            }
            else if (board_to_check[x - 1][y - 1] == 'X' || board_to_check[x - 1][y - 1] == 'O') {
                Exceptions<ERRORS>exception(ER_FIELD_CHECKED);
                throw exception;
            }
            else
                t = true;
        }
        catch(Exceptions<ERRORS>e) {
            Exceptions<ERRORS>::manageException(reinterpret_cast<ERRORS &>(e));
        }
    }
    if (board[x - 1][y - 1] == 'X')
    {
        board_to_check[x - 1][y - 1] = 'X';
        cout << "Good job you've hit the ship ! Your turn" << endl;
        Sleep(1500);
        hit_ship_p[nr - 1] = board_s[x - 1][y - 1];
        p_hit[nr - 1]++;
        if (hit_ship_p[nr - 1] == ONE) {
            cout << "A single mast was sunk!" << endl;
            if (x - 2 >= 0) {
                board_to_check[x - 2][y - 1] = 'O';
                if (y - 2 >= 0) {
                    board_to_check[x - 2][y - 2] = 'O';
                }
                if (y < 10) {
                    board_to_check[x - 2][y] = 'O';
                }
            }
            if (y - 2 >= 0) {
                board_to_check[x - 1][y - 2] = 'O';
                if (x < 10) {
                    board_to_check[x][y - 2] = 'O';
                }
            }
            if (y < 10) {
                board_to_check[x - 1][y] = 'O';
                if (x < 10) {
                    board_to_check[x][y] = 'O';
                }
            }
            if (x < 10) {
                board_to_check[x][y - 1] = 'O';
            }
            Sleep(1111);
            p_hit[nr - 1] = 0;
            hit_ship_p[nr - 1] = EMPTY;
        }
        else if (hit_ship_p[nr - 1] == TWO && p_hit[nr - 1] == 2) {
            cout << "A two-masted ship was sunk!" << endl;

            if ((x - 1 >= 0 && y < 10) && (board[x - 1][y] == 'X')) {

                if (x - 2 >= 0) {
                    board_to_check[x - 2][y - 1] = 'O';
                    board_to_check[x - 2][y] = 'O';
                    if (y - 2 >= 0) {
                        board_to_check[x - 2][y - 2] = 'O';
                    }
                    if (y + 1 < 10) {
                        board_to_check[x - 2][y + 1] = 'O';
                    }
                }
                if (y - 2 >= 0) {
                    board_to_check[x - 1][y - 2] = 'O';
                }
                if (y + 1 < 10) {
                    board_to_check[x - 1][y + 1] = 'O';
                }
                if (x < 10) {
                    board_to_check[x][y - 1] = 'O';
                    board_to_check[x][y] = 'O';
                    if (y - 2 >= 0) {
                        board_to_check[x][y - 2] = 'O';
                    }
                    if (y + 1 < 10) {
                        board_to_check[x][y + 1] = 'O';
                    }
                }
            }

            else if ((x - 1 >= 0 && y - 2 >= 0) && (board[x - 1][y - 2] == 'X')) {

                if (x - 2 >= 0) {
                    board_to_check[x - 2][y - 2] = 'O';
                    board_to_check[x - 2][y - 1] = 'O';
                    if (y - 3 >= 0) {
                        board_to_check[x - 2][y - 3] = 'O';
                    }
                    if (y < 10) {
                        board_to_check[x - 2][y] = 'O';
                    }
                }
                if (y - 3 >= 0) {
                    board_to_check[x - 1][y - 3] = 'O';
                }
                if (y < 10) {
                    board_to_check[x - 1][y] = 'O';
                }
                if (x < 10) {
                    board_to_check[x][y - 2] = 'O';
                    board_to_check[x][y - 1] = 'O';
                    if (y - 3 >= 0) {
                        board_to_check[x][y - 3] = 'O';
                    }
                    if (y < 10) {
                        board_to_check[x][y] = 'O';
                    }
                }

            }
            else if ((x - 2 >= 0 && y - 1 >= 0) && (board[x - 2][y - 1] == 'X')) {

                if (x - 3 >= 0) {
                    board_to_check[x - 3][y - 1] = 'O';
                    if (y - 2 >= 0) {
                        board_to_check[x - 3][y - 2] = 'O';
                    }
                    if (y < 10) {
                        board_to_check[x - 3][y] = 'O';
                    }
                }
                if (y - 2 >= 0) {
                    board_to_check[x - 2][y - 2] = 'O';
                    board_to_check[x - 1][y - 2] = 'O';
                    if (x < 10) {
                        board_to_check[x][y - 2] = 'O';
                    }
                }
                if (y < 10) {
                    board_to_check[x - 2][y] = 'O';
                    board_to_check[x - 1][y] = 'O';
                    if (x < 10) {
                        board_to_check[x][y] = 'O';
                    }
                }
                if (x < 10) {
                    board_to_check[x][y - 1] = 'O';
                }
            }
            else if ((x < 10 && y - 1 >= 0) && (board[x][y - 1] == 'X')) {

                if (x - 2 >= 0) {
                    board_to_check[x - 2][y - 1] = 'O';
                    if (y - 2 >= 0) {
                        board_to_check[x - 2][y - 2] = 'O';
                    }
                    if (y < 10) {
                        board_to_check[x - 2][y] = 'O';
                    }
                }
                if (y - 2 >= 0) {
                    board_to_check[x - 1][y - 2] = 'O';
                    board_to_check[x][y - 2] = 'O';
                    if (x + 1 < 10) {
                        board_to_check[x + 1][y - 2] = 'O';
                    }
                }
                if (y < 10) {
                    board_to_check[x - 1][y] = 'O';
                    board_to_check[x][y] = 'O';
                    if (x + 1 < 10) {
                        board_to_check[x + 1][y] = 'O';
                    }
                }
                if (x + 1 < 10) {
                    board_to_check[x + 1][y - 1] = 'O';
                }
            }

            Sleep(1111);
            p_hit[nr - 1] = 0;
            hit_ship_p[nr - 1] = EMPTY;
        }
        else if (hit_ship_p[nr - 1] == THREE && p_hit[nr - 1] == 3) {
            cout << "A three-masted ship was sunk!" << endl;
            if ((x - 1 >= 0 && y < 10) && (board[x - 1][y] == 'X')) {

                if (x - 2 >= 0) {
                    board_to_check[x - 2][y - 1] = 'O';
                    board_to_check[x - 2][y] = 'O';
                    board_to_check[x - 2][y + 1] = 'O';
                    if (y - 2 >= 0) {
                        board_to_check[x - 2][y - 2] = 'O';
                    }
                    if (y + 2 < 10) {
                        board_to_check[x - 2][y + 2] = 'O';
                    }
                }
                if (y - 2 >= 0) {
                    board_to_check[x - 1][y - 2] = 'O';
                }
                if (y + 2 < 10) {
                    board_to_check[x - 1][y + 2] = 'O';
                }
                if (x < 10) {
                    board_to_check[x][y - 1] = 'O';
                    board_to_check[x][y] = 'O';
                    board_to_check[x][y + 1] = 'O';
                    if (y - 2 >= 0) {
                        board_to_check[x][y - 2] = 'O';
                    }
                    if (y + 2 < 10) {
                        board_to_check[x][y + 2] = 'O';
                    }
                }

            }
            else if ((x - 1 >= 0 && y - 2 >= 0) && (board[x - 1][y - 2] == 'X')) {

                if (x - 2 >= 0) {
                    board_to_check[x - 2][y - 1] = 'O';
                    board_to_check[x - 2][y - 2] = 'O';
                    board_to_check[x - 2][y - 3] = 'O';
                    if (y - 4 >= 0) {
                        board_to_check[x - 2][y - 4] = 'O';
                    }
                    if (y < 10) {
                        board_to_check[x - 2][y] = 'O';
                    }
                }
                if (y - 4 >= 0) {
                    board_to_check[x - 1][y - 4] = 'O';
                }
                if (y < 10) {
                    board_to_check[x - 1][y] = 'O';
                }
                if (x < 10) {
                    board_to_check[x][y - 1] = 'O';
                    board_to_check[x][y - 2] = 'O';
                    board_to_check[x][y - 3] = 'O';
                    if (y - 4 >= 0) {
                        board_to_check[x][y - 4] = 'O';
                    }
                    if (y < 10) {
                        board_to_check[x][y] = 'O';
                    }
                }
            }
            else if ((x - 2 >= 0 && y - 1 >= 0) && (board[x - 2][y - 1] == 'X')) {
                if (x - 4 >= 0)
                {
                    board_to_check[x - 4][y - 1] = 'O';
                    if (y - 2 >= 0) {
                        board_to_check[x - 4][y - 2] = 'O';
                    }
                    if (y < 10) {
                        board_to_check[x - 4][y] = 'O';
                    }
                }
                if (y - 2 >= 0) {
                    board_to_check[x - 3][y - 2] = 'O';
                    board_to_check[x - 2][y - 2] = 'O';
                    board_to_check[x - 1][y - 2] = 'O';
                    if (x < 10) {
                        board_to_check[x][y - 2] = 'O';
                    }
                }
                if (y < 10) {
                    board_to_check[x - 3][y] = 'O';
                    board_to_check[x - 2][y] = 'O';
                    board_to_check[x - 1][y] = 'O';
                    if (x < 10) {
                        board_to_check[x][y] = 'O';
                    }
                }
                if (x < 10) {
                    board_to_check[x][y - 1] = 'O';
                }
            }
            else if ((x < 10 && y - 1 >= 0) && (board[x][y - 1] == 'X')) {
                if (x - 2 >= 0) {
                    board_to_check[x - 2][y - 1] = 'O';
                    if (y - 2 >= 0) {
                        board_to_check[x - 2][y - 2] = 'O';
                    }
                    if (y < 10) {
                        board_to_check[x - 2][y] = 'O';
                    }
                }
                if (y - 2 >= 0) {
                    board_to_check[x - 1][y - 2] = 'O';
                    board_to_check[x][y - 2] = 'O';
                    board_to_check[x + 1][y - 2] = 'O';
                    if (x + 2 < 10) {
                        board_to_check[x + 2][y - 2] = 'O';
                    }
                }
                if (y < 10) {
                    board_to_check[x - 1][y] = 'O';
                    board_to_check[x][y] = 'O';
                    board_to_check[x + 1][y] = 'O';
                    if (x + 2 < 10) {
                        board_to_check[x + 2][y] = 'O';
                    }
                }
                if (x + 2 < 10) {
                    board_to_check[x + 2][y - 1] = 'O';
                }
            }
            Sleep(1111);
            p_hit[nr - 1] = 0;
            hit_ship_p[nr - 1] = EMPTY;
        }
        else if (hit_ship_p[nr - 1] == FOUR && p_hit[nr - 1] == 4) {
            cout << "A four-masted ship was sunk!" << endl;
            if ((x - 1 >= 0 && y < 10) && (board[x - 1][y] == 'X')) {
                if (x - 2 >= 0) {
                    board_to_check[x - 2][y - 1] = 'O';
                    board_to_check[x - 2][y] = 'O';
                    board_to_check[x - 2][y + 1] = 'O';
                    board_to_check[x - 2][y + 2] = 'O';
                    if (y - 2 >= 0) {
                        board_to_check[x - 2][y - 2] = 'O';
                    }
                    if (y + 3 < 10) {
                        board_to_check[x - 2][y + 3] = 'O';
                    }
                }
                if (y - 2 >= 0) {
                    board_to_check[x - 1][y - 2] = 'O';
                }
                if (y + 3 < 10) {
                    board_to_check[x - 1][y + 3] = 'O';
                }
                if (x < 10) {
                    board_to_check[x][y - 1] = 'O';
                    board_to_check[x][y] = 'O';
                    board_to_check[x][y + 1] = 'O';
                    board_to_check[x][y + 2] = 'O';
                    if (y - 2 >= 0) {
                        board_to_check[x][y - 2] = 'O';
                    }
                    if (y + 3 < 10) {
                        board_to_check[x][y + 3] = 'O';
                    }
                }
            }
            else if ((x - 1 >= 0 && y - 2 >= 0) && (board[x - 1][y - 2] == 'X')) {
                if (x - 2 >= 0) {
                    board_to_check[x - 2][y - 1] = 'O';
                    board_to_check[x - 2][y - 2] = 'O';
                    board_to_check[x - 2][y - 3] = 'O';
                    board_to_check[x - 2][y - 4] = 'O';
                    if (y - 5 >= 0) {
                        board_to_check[x - 2][y - 5] = 'O';
                    }
                    if (y < 10) {
                        board_to_check[x - 2][y] = 'O';
                    }
                }
                if (y - 5 >= 0) {
                    board_to_check[x - 1][y - 5] = 'O';
                }
                if (y < 10) {
                    board_to_check[x - 1][y] = 'O';
                }
                if (x < 10) {
                    board_to_check[x][y - 1] = 'O';
                    board_to_check[x][y - 2] = 'O';
                    board_to_check[x][y - 3] = 'O';
                    board_to_check[x][y - 4] = 'O';
                    if (y - 5 >= 0) {
                        board_to_check[x][y - 5] = 'O';
                    }
                    if (y < 10) {
                        board_to_check[x][y] = 'O';
                    }
                }
            }
            else if ((x - 2 >= 0 && y - 1 >= 0) && (board[x - 2][y - 1] == 'X')) {
                if (x - 5 >= 0) {
                    board_to_check[x - 5][y - 1] = 'O';
                    if (y - 2 >= 0) {
                        board_to_check[x - 5][y - 2] = 'O';
                    }
                    if (y < 10) {
                        board_to_check[x - 5][y] = 'O';
                    }
                }
                if (y - 2 >= 0) {
                    board_to_check[x - 4][y - 2] = 'O';
                    board_to_check[x - 3][y - 2] = 'O';
                    board_to_check[x - 2][y - 2] = 'O';
                    board_to_check[x - 1][y - 2] = 'O';
                    if (x < 10) {
                        board_to_check[x][y - 2] = 'O';
                    }
                }
                if (y < 10) {
                    board_to_check[x - 4][y] = 'O';
                    board_to_check[x - 3][y] = 'O';
                    board_to_check[x - 2][y] = 'O';
                    board_to_check[x - 1][y] = 'O';
                    if (x < 10) {
                        board_to_check[x][y] = 'O';
                    }
                }
                if (x < 10) {
                    board_to_check[x][y - 1] = 'O';
                }
            }
            else if ((x < 10 && y - 1 >= 0) && (board[x][y - 1] == 'X')) {
                if (x - 2 >= 0) {
                    board_to_check[x - 2][y - 1] = 'O';
                    if (y - 2 >= 0) {
                        board_to_check[x - 2][y - 2] = 'O';
                    }
                    if (y < 10) {
                        board_to_check[x - 2][y] = 'O';
                    }
                }
                if (y - 2 >= 0) {
                    board_to_check[x - 1][y - 2] = 'O';
                    board_to_check[x][y - 2] = 'O';
                    board_to_check[x + 1][y - 2] = 'O';
                    board_to_check[x + 2][y - 2] = 'O';
                    if (x + 3 < 10) {
                        board_to_check[x + 3][y - 2] = 'O';
                    }
                }
                if (y < 10) {
                    board_to_check[x - 1][y] = 'O';
                    board_to_check[x][y] = 'O';
                    board_to_check[x + 1][y] = 'O';
                    board_to_check[x + 2][y] = 'O';
                    if (x + 3 < 10) {
                        board_to_check[x + 3][y] = 'O';
                    }
                }
                if (x + 3 < 10) {
                    board_to_check[x + 3][y - 1] = 'O';
                }
            }
            Sleep(1111);
            p_hit[nr - 1] = 0;
            hit_ship_p[nr - 1] = EMPTY;
        }

        if (CurrentPlayer == PLAYER1) {
            points_1++;
            ++dynamic_cast<Player&>(*p1);
            Game::Check();
        }
        else if(CurrentPlayer == PLAYER2) {
            ++dynamic_cast<Player&>(*p2);
            Game::Check();
        }
    }
    else
    {
        board_to_check[x - 1][y - 1] = 'O';
        cout << "You missed! End of your turn" << endl;
        Sleep(1500);
        if (mode == '1') {
            if (CurrentPlayer == PLAYER1) CurrentPlayer = PLAYER2;
            else CurrentPlayer = PLAYER1;
        }
        else if (mode == '2') {
            CurrentPlayer = COMPUTER;
        }
    }
}
void Player::SetShips()
{
    int choice;
    cout << "Do you want to place the ships by yourself or do you want to autoset the ships?" << endl;
    cout << "1.On your own" << endl;
    cout << "2.Autoset" << endl;
    cout << "Your choice 1/2 :";
    choice = _getch();
    while (char(choice) != '1' && char(choice) != '2')
        choice = _getch();
    if (char(choice) == '1') {
        SetShip(1, FOUR);
        SetShip(1, THREE);
        SetShip(1, THREE);
        SetShip(1, TWO);
        SetShip(1, TWO);
        SetShip(1, TWO);
        SetShip(1, ONE);
        SetShip(1, ONE);
        SetShip(1, ONE);
        SetShip(1, ONE);
    }
    else if (char(choice) == '2')
    {
        autoset(this, 4, FOUR);
        autoset(this, 3, THREE);
        autoset(this, 3, THREE);
        autoset(this, 2, TWO);
        autoset(this, 2, TWO);
        autoset(this, 2, TWO);
        autoset(this, 1, ONE);
        autoset(this, 1, ONE);
        autoset(this, 1, ONE);
        autoset(this, 1, ONE);
    }
}

Comp::Comp(string n)
{
    nick = n;
    points = 0;
}
Comp::Comp()
{
    nick = "Computer";
    points = 0;
}
Comp::~Comp()
{
    for (int i = 0; i < 10; i++)
    {
        delete[] board[i];
        delete[] board_to_check[i];
        delete[] board_s[i];
    }
    delete[] board;
    delete[] board_to_check;
    delete[] board_s;
}
void Comp::SetBoard()
{
    board = new char* [SIZE];
    board_to_check = new char* [SIZE];
    board_s = new SHIPS * [SIZE];
    for (int i = 0; i < SIZE; i++)
    {
        board[i] = new char[SIZE];
        board_to_check[i] = new char[SIZE];
        board_s[i] = new SHIPS[SIZE];
    }
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            board[i][j] = '?';
            board_to_check[i][j] = '?';
            board_s[i][j] = EMPTY;
        }
    }
}
void Comp::SetShips()
{
    SetShip(4, FOUR);
    SetShip(3, THREE);
    SetShip(3, THREE);
    SetShip(2, TWO);
    SetShip(2, TWO);
    SetShip(2, TWO);
    SetShip(1, ONE);
    SetShip(1, ONE);
    SetShip(1, ONE);
    SetShip(1, ONE);
}
void Comp::SetShip(int length, SHIPS s)
{
    int x_begin, y_begin;
    int x_end, y_end;
    DIRECTION k;
    bool t = false;

    while (!t)
    {
        x_begin = rand() % 10 + 1;
        y_begin = rand() % 10 + 1;
        k = ((rand() % 4 + 1) % 2 == 0 ? VERTICAL : HORIZONTAL);

        x_begin--; y_begin--;
        if (k == HORIZONTAL) {
            if (x_begin + length < 10)
            {
                if (check(x_begin, y_begin, x_begin + length, y_begin, length, this->board)) {
                    x_end = x_begin + length;
                    y_end = y_begin;
                    for (int i = x_begin; i < x_begin + length; i++) {
                        board[i][y_begin] = 'X';
                        board_s[i][y_begin] = s;
                    }

                    if (x_begin - 1 >= 0)
                    {
                        board[x_begin - 1][y_begin] = 'O';
                        if (y_begin - 1 >= 0) {
                            board[x_begin - 1][y_begin] = 'O';
                        }
                        if (y_begin + 1 < 10) {
                            board[x_begin - 1][y_begin + 1] = 'O';
                        }
                    }

                    for (int i = 0; i < length; i++) {
                        if (y_begin - 1 >= 0) {
                            board[x_begin + i][y_begin - 1] = 'O';
                        }
                        if (y_begin + 1 < 10) {
                            board[x_begin + i][y_begin + 1] = 'O';
                        }
                    }
                    if (x_begin + length < 10) {
                        if (y_begin - 1 >= 0) {
                            board[x_begin + length][y_begin - 1] = 'O';
                        }
                        if (y_begin + 1 < 10) {
                            board[x_begin + length][y_begin + 1] = 'O';
                        }
                        board[x_begin + length][y_begin] = 'O';
                    }
                    {
                        t = true;
                    }
                }
            }
            else if (x_begin + length >= 10 && x_begin - length >= 0)
            {
                if (check(x_begin, y_begin, x_begin - length, y_begin, length, this->board)) {
                    x_end = x_begin - length;
                    y_end = y_begin;
                    for (int i = x_end; i < x_end + length; i++) {
                        board[i][y_end] = 'X';
                        board_s[i][y_end] = s;
                    }

                    if (x_end - 1 >= 0)
                    {
                        board[x_end - 1][y_end] = 'O';
                        if (y_end - 1 >= 0) {
                            board[x_end - 1][y_end] = 'O';
                        }
                        if (y_end + 1 < 10) {
                            board[x_end - 1][y_end + 1] = 'O';
                        }
                    }
                    for (int i = 0; i < length; i++) {
                        if (y_end - 1 >= 0) {
                            board[x_end + length][y_end - 1] = 'O';
                        }
                        if (y_end + 1 < 10) {
                            board[x_end + length][y_end + 1] = 'O';
                        }
                    }
                    if (x_end + length < 10) {
                        if (y_end - 1 >= 0) {
                            board[x_end + length][y_end - 1] = 'O';
                        }
                        if (y_begin + 1 < 10) {
                            board[x_end + length][y_end + 1] = 'O';
                        }
                        board[x_end + length][y_end] = 'O';
                    }
                    t = true;
                }
            }
        }
        else if (k == VERTICAL) {
            if (y_begin + length < 10) {
                if (check(x_begin, y_begin, x_begin, y_begin + length, length, this->board)) {
                    x_end = x_begin;
                    y_end = y_begin + length;
                    for (int i = y_begin; i < y_begin + length; i++) {
                        board[x_begin][i] = 'X';
                        board_s[x_begin][i] = s;
                    }
                    if (y_begin - 1 >= 0) {
                        if (x_begin - 1 >= 0) {
                            board[x_begin - 1][y_begin - 1] = 'O';
                        }
                        if (x_begin + 1 < 10) {
                            board[x_begin + 1][y_begin - 1] = 'O';
                        }
                        board[x_begin][y_begin - 1] = 'O';
                    }
                    if (y_begin + length < 10) {
                        if (x_begin - 1 >= 0) {
                            board[x_begin - 1][y_begin + length] = 'O';
                        }
                        if (x_begin + 1 < 10) {
                            board[x_begin + 1][y_begin + length] = 'O';
                        }
                        board[x_begin][y_begin + length] = 'O';
                    }
                    for (int i = 0; i < length; i++) {
                        if (x_begin - 1 >= 0) {
                            board[x_begin - 1][y_begin + i] = 'O';
                        }
                        if (x_begin + 1 < 10) {
                            board[x_begin + 1][y_begin + i] = 'O';
                        }
                    }

                    t = true;
                }
            }
            else if (y_begin + length >= 10 && y_begin - length >= 0) {
                if (check(x_begin, y_begin, x_begin, y_begin - length, length, this->board)) {
                    x_end = x_begin;
                    y_end = y_begin - length;
                    for (int i = y_end; i < y_end + length; i++) {
                        board[x_end][i] = 'X';
                        board_s[x_end][i] = s;
                    }
                    if (y_end - 1 >= 0) {
                        if (x_end - 1 >= 0) {
                            board[x_end - 1][y_end - 1] = 'O';
                        }
                        if (x_end + 1 < 10) {
                            board[x_end + 1][y_end - 1] = 'O';
                        }
                        board[x_end][y_end - 1] = 'O';
                    }
                    if (y_end + length < 10) {
                        if (x_end - 1 >= 0) {
                            board[x_end - 1][y_end + length] = 'O';
                        }
                        if (x_begin + 1 < 10) {
                            board[x_end + 1][y_end + length] = 'O';
                        }
                        board[x_end][y_end + length] = 'O';
                    }
                    for (int i = 0; i < length; i++) {
                        if (x_end - 1 >= 0) {
                            board[x_end - 1][y_end + i] = 'O';
                        }
                        if (x_end + 1 < 10) {
                            board[x_end + 1][y_end + i] = 'O';
                        }
                    }
                    t = true;
                }
            }
        }
    }

}
void Comp::operator++()
{
    points++;
}
void Comp::Move(char** board, char** board_to_check, SHIPS** board_s)
{
    int x, y;
    if (hit_ship_c == EMPTY)
    {
        bool t = false;
        while (!t) {
            x = rand() % 10 + 1;
            y = rand() % 10 + 1;
            if (!if_checked(x, y)) {
                t = true;
                checked_coordinates.push_back(make_pair(x, y));
            }
        }
        cout << "Checking coordinates (" << x << " , " << y << ")" << endl;
        Sleep(1500);
        if (board[x - 1][y - 1] == 'X')
        {
            board_to_check[x - 1][y - 1] = 'X';
            cout << "Good job you've hit the ship ! Your turn" << endl;
            hit_ship_c = board_s[x - 1][y - 1];
            good_x = x;
            good_y = y;
            Sleep(1500);
            ++dynamic_cast<Comp&>(*AI);
            c_hit++;
            direction = VERTICAL;

            if (hit_ship_c == ONE) {
                cout << "A single mast was sunk! Your turn" << endl;
                Sleep(1500);
                hit_ship_c = EMPTY;
                int i, j;
                i = good_x - 2;
                j = good_y - 2;
                c_hit = 0;
                direction = NONE;
                if (i >= 0 && j >= 0) {
                    board_to_check[i][j] = 'O';
                    checked_coordinates.push_back(make_pair(i + 1, j + 1));
                }
                j++;
                if (i >= 0 && j >= 0 && j < 10) {
                    board_to_check[i][j] = 'O';
                    checked_coordinates.push_back(make_pair(i + 1, j + 1));
                }
                j++;
                if (i >= 0 && j >= 0 && j < 10) {
                    board_to_check[i][j] = 'O';
                    checked_coordinates.push_back(make_pair(i + 1, j + 1));
                }
                i++;
                j = good_y - 2;
                if (j >= 0) {
                    board_to_check[i][j] = 'O';
                    checked_coordinates.push_back(make_pair(i + 1, j + 1));
                }
                j += 2;
                if (j >= 0 && j < 10) {
                    board_to_check[i][j] = 'O';
                    checked_coordinates.push_back(make_pair(i + 1, j + 1));
                }
                i++;
                j = good_y - 2;
                if (i < 10 && j >= 0) {
                    board_to_check[i][j] = 'O';
                    checked_coordinates.push_back(make_pair(i + 1, j + 1));
                }
                j++;
                if (i < 10 && j < 10) {
                    board_to_check[i][j] = 'O';
                    checked_coordinates.push_back(make_pair(i + 1, j + 1));
                }
                j++;
                if (i < 10 && j < 10) {
                    board_to_check[i][j] = 'O';
                    checked_coordinates.push_back(make_pair(i + 1, j + 1));
                }
                good_x = 0;
                good_y = 0;
                Game::Check();
            }
        }
        else
        {
            board_to_check[x - 1][y - 1] = 'O';
            cout << "You missed! End of your turn" << endl;
            Sleep(1500);
            CurrentPlayer = PLAYER1;
        }
    }
    else
    {
        if (hit_ship_c == TWO)
        {
            if (good_x + 1 <= 10 && !if_checked(good_x + 1, good_y)) {
                cout << "Checking coordinates (" << good_x + 1 << " , " << good_y << ")" << endl;
                if (board[good_x][good_y - 1] == 'X')
                {
                    board_to_check[good_x][good_y - 1] = 'X';
                    cout << "A two-masted ship was sunk! Your turn" << endl;
                    Sleep(2000);
                    hit_ship_c = EMPTY;
                    checked_coordinates.push_back(make_pair(good_x + 1, good_y));
                    c_hit = 0;
                    int i, j;
                    i = good_x - 2;
                    j = good_y - 2;
                    if (i >= 0 && j >= 0) {
                        board_to_check[i][j] = 'O';
                        checked_coordinates.push_back(make_pair(i + 1, j + 1));
                    }
                    j++;
                    if (i >= 0 && j >= 0 && j < 10) {
                        board_to_check[i][j] = 'O';
                        checked_coordinates.push_back(make_pair(i + 1, j + 1));
                    }
                    j++;
                    if (i >= 0 && j >= 0 && j < 10) {
                        board_to_check[i][j] = 'O';
                        checked_coordinates.push_back(make_pair(i + 1, j + 1));
                    }
                    i++;
                    j = good_y - 2;
                    if (j >= 0) {
                        board_to_check[i][j] = 'O';
                        checked_coordinates.push_back(make_pair(i + 1, j + 1));
                    }
                    j += 2;
                    if (j < 10) {
                        board_to_check[i][j] = 'O';
                        checked_coordinates.push_back(make_pair(i + 1, j + 1));
                    }
                    i++;
                    j = good_y - 2;
                    if (j >= 0) {
                        board_to_check[i][j] = 'O';
                        checked_coordinates.push_back(make_pair(i + 1, j + 1));
                    }
                    j += 2;
                    if (j < 10) {
                        board_to_check[i][j] = 'O';
                        checked_coordinates.push_back(make_pair(i + 1, j + 1));
                    }
                    i++;
                    j = good_y - 2;
                    if (i < 10 && j >= 0) {
                        board_to_check[i][j] = 'O';
                        checked_coordinates.push_back(make_pair(i + 1, j + 1));
                    }
                    j++;
                    if (i < 10 && j < 10) {
                        board_to_check[i][j] = 'O';
                        checked_coordinates.push_back(make_pair(i + 1, j + 1));
                    }
                    j++;
                    if (i < 10 && j < 10) {
                        board_to_check[i][j] = 'O';
                        checked_coordinates.push_back(make_pair(i + 1, j + 1));
                    }

                    good_x = 0;
                    good_y = 0;
                    ++dynamic_cast<Comp&>(*AI);
                    Game::Check();
                }
                else
                {
                    board_to_check[good_x][good_y - 1] = 'O';
                    cout << "You missed! End of your turn" << endl;
                    Sleep(1500);
                    checked_coordinates.push_back(make_pair(good_x + 1, good_y));
                    CurrentPlayer = PLAYER1;
                }

            }
            else if (good_x - 1 >= 1 && !if_checked(good_x - 1, good_y)) {
                cout << "Checking coordinates (" << good_x - 1 << " , " << good_y << ")" << endl;
                if (board[good_x - 2][good_y - 1] == 'X')
                {
                    board_to_check[good_x - 2][good_y - 1] = 'X';
                    cout << "A two-masted ship was sunk! Your turn" << endl;
                    Sleep(2000);
                    hit_ship_c = EMPTY;
                    checked_coordinates.push_back(make_pair(good_x - 1, good_y));
                    c_hit = 0;
                    good_x -= 1;
                    int i, j;
                    i = good_x - 2;
                    j = good_y - 2;
                    if (i >= 0 && j >= 0) {
                        board_to_check[i][j] = 'O';
                        checked_coordinates.push_back(make_pair(i + 1, j + 1));
                    }
                    j++;
                    if (i >= 0 && j >= 0 && j < 10) {
                        board_to_check[i][j] = 'O';
                        checked_coordinates.push_back(make_pair(i + 1, j + 1));
                    }
                    j++;
                    if (i >= 0 && j >= 0 && j < 10) {
                        board_to_check[i][j] = 'O';
                        checked_coordinates.push_back(make_pair(i + 1, j + 1));
                    }
                    i++;
                    j = good_y - 2;
                    if (j >= 0) {
                        board_to_check[i][j] = 'O';
                        checked_coordinates.push_back(make_pair(i + 1, j + 1));
                    }
                    j += 2;
                    if (j < 10) {
                        board_to_check[i][j] = 'O';
                        checked_coordinates.push_back(make_pair(i + 1, j + 1));
                    }
                    i++;
                    j = good_y - 2;
                    if (j >= 0) {
                        board_to_check[i][j] = 'O';
                        checked_coordinates.push_back(make_pair(i + 1, j + 1));
                    }
                    j += 2;
                    if (j < 10) {
                        board_to_check[i][j] = 'O';
                        checked_coordinates.push_back(make_pair(i + 1, j + 1));
                    }
                    i++;
                    j = good_y - 2;
                    if (i < 10 && j >= 0) {
                        board_to_check[i][j] = 'O';
                        checked_coordinates.push_back(make_pair(i + 1, j + 1));
                    }
                    j++;
                    if (i < 10 && j < 10) {
                        board_to_check[i][j] = 'O';
                        checked_coordinates.push_back(make_pair(i + 1, j + 1));
                    }
                    j++;
                    if (i < 10 && j < 10) {
                        board_to_check[i][j] = 'O';
                        checked_coordinates.push_back(make_pair(i + 1, j + 1));
                    }

                    good_x = 0;
                    good_y = 0;
                    ++dynamic_cast<Comp&>(*AI);
                    Game::Check();
                }
                else
                {
                    board_to_check[good_x - 2][good_y - 1] = 'O';
                    cout << "You missed! End of your turn" << endl;
                    Sleep(1500);
                    checked_coordinates.push_back(make_pair(good_x - 1, good_y));
                    CurrentPlayer = PLAYER1;
                }

            }
            else if (good_y + 1 <= 10 && !if_checked(good_x, good_y + 1))
            {
                cout << "Checking coordinates (" << good_x << " , " << good_y + 1 << ")" << endl;
                if (board[good_x - 1][good_y] == 'X')
                {
                    board_to_check[good_x - 1][good_y] = 'X';
                    cout << "A two-masted ship was sunk! Your turn" << endl;
                    Sleep(2000);
                    hit_ship_c = EMPTY;
                    c_hit = 0;
                    checked_coordinates.push_back(make_pair(good_x, good_y + 1));
                    int i, j;
                    i = good_x - 2;
                    j = good_y - 2;
                    if (i >= 0 && j >= 0) {
                        board_to_check[i][j] = 'O';
                    }
                    j++;
                    if (i >= 0 && j >= 0 && j < 10) {
                        board_to_check[i][j] = 'O';
                    }
                    j++;
                    if (i >= 0 && j > 0 && j < 10) {
                        board_to_check[i][j] = 'O';
                    }
                    j++;
                    if (i >= 0 && j > 0 && j < 10) {
                        board_to_check[i][j] = 'O';
                    }
                    i++;
                    j = good_y - 2;
                    if (j >= 0) {
                        board_to_check[i][j] = 'O';
                    }
                    j += 3;
                    if (j < 10) {
                        board_to_check[i][j] = 'O';
                    }
                    i++;
                    j = good_y - 2;
                    if (i < 10 && j >= 0) {
                        board_to_check[i][j] = 'O';
                    }
                    j++;
                    if (i < 10 && j >= 0 && j < 10) {
                        board_to_check[i][j] = 'O';
                    }
                    j++;
                    if (i < 10 && j >= 0 && j < 10) {
                        board_to_check[i][j] = 'O';
                    }
                    j++;
                    if (i < 10 && j >= 0 && j < 10) {
                        board_to_check[i][j] = 'O';
                    }
                    good_x = 0;
                    good_y = 0;
                    ++dynamic_cast<Comp&>(*AI);
                    Game::Check();
                }
                else
                {
                    board_to_check[good_x - 1][good_y] = 'O';
                    cout << "You missed! End of your turn" << endl;
                    Sleep(1500);
                    checked_coordinates.push_back(make_pair(good_x, good_y + 1));
                    CurrentPlayer = PLAYER1;
                }

            }
            else if (good_y - 1 >= 1 && !if_checked(good_x, good_y - 1))
            {
                cout << "Checking coordinates (" << good_x << " , " << good_y - 1 << ")" << endl;
                if (board[good_x - 1][good_y - 2] == 'X')
                {
                    board_to_check[good_x - 1][good_y - 2] = 'X';
                    cout << "A two-masted ship was sunk! Your turn" << endl;
                    Sleep(2000);
                    hit_ship_c = EMPTY;
                    checked_coordinates.push_back(make_pair(good_x, good_y - 1));
                    c_hit = 0;
                    good_y -= 1;
                    int i, j;
                    i = good_x - 2;
                    j = good_y - 2;
                    if (i >= 0 && j >= 0) {
                        board_to_check[i][j] = 'O';
                    }
                    j++;
                    if (i >= 0 && j >= 0 && j < 10) {
                        board_to_check[i][j] = 'O';
                    }
                    j++;
                    if (i >= 0 && j > 0 && j < 10) {
                        board_to_check[i][j] = 'O';
                    }
                    j++;
                    if (i >= 0 && j > 0 && j < 10) {
                        board_to_check[i][j] = 'O';
                    }
                    i++;
                    j = good_y - 2;
                    if (j >= 0) {
                        board_to_check[i][j] = 'O';
                    }
                    j += 3;
                    if (j < 10) {
                        board_to_check[i][j] = 'O';
                    }
                    i++;
                    j = good_y - 2;
                    if (i < 10 && j >= 0) {
                        board_to_check[i][j] = 'O';
                    }
                    j++;
                    if (i < 10 && j >= 0 && j < 10) {
                        board_to_check[i][j] = 'O';
                    }
                    j++;
                    if (i < 10 && j >= 0 && j < 10) {
                        board_to_check[i][j] = 'O';
                    }
                    j++;
                    if (i < 10 && j >= 0 && j < 10) {
                        board_to_check[i][j] = 'O';
                    }
                    good_x = 0;
                    good_y = 0;
                    ++dynamic_cast<Comp&>(*AI);
                    Game::Check();
                }
                else
                {
                    board_to_check[good_x - 1][good_y - 2] = 'O';
                    cout << "You missed! End of your turn" << endl;
                    Sleep(1500);
                    checked_coordinates.push_back(make_pair(good_x, good_y - 1));
                    CurrentPlayer = PLAYER1;
                }
            }
        }
        else if (hit_ship_c == THREE)
        {
            if (direction == VERTICAL) {

                if (!(good_x + 1 <= 10 && !if_checked(good_x + 1, good_y)) && !(good_x - 1 >= 1 && !if_checked(good_x - 1, good_y))) {
                    if (c_hit == 1)
                        direction = HORIZONTAL;
                    if (c_hit == 2) {
                        good_x -= 1;
                    }
                }
                if (good_x + 1 <= 10 && !if_checked(good_x + 1, good_y))
                {
                    cout << "Checking coordinates (" << good_x + 1 << " , " << good_y << ")" << endl;
                    if (board[good_x][good_y - 1] == 'X') {
                        points_2++;
                        c_hit++;
                        if (c_hit != 3) {
                            cout << "Good job you've hit the ship ! Your turn" << endl;
                            board_to_check[good_x][good_y - 1] = 'X';
                            Sleep(1500);
                            checked_coordinates.push_back(make_pair(good_x + 1, good_y));
                            good_x += 1;
                        }
                        else if (c_hit == 3) {
                            cout << "A three-masted ship was sunk! Your turn" << endl;
                            board_to_check[good_x][good_y - 1] = 'X';
                            Sleep(1500);
                            checked_coordinates.push_back(make_pair(good_x + 1, good_y));

                            int i, j;
                            i = good_x - 3;
                            j = good_y - 2;
                            if (i >= 0 && j >= 0) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            j++;
                            if (i >= 0 && j >= 0 && j < 10) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            j++;
                            if (i >= 0 && j >= 0 && j < 10) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            i++;
                            j = good_y - 2;
                            if (j >= 0) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            j += 2;
                            if (j < 10) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            i++;
                            j = good_y - 2;
                            if (j >= 0) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            j += 2;
                            if (j < 10) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            i++;
                            j = good_y - 2;
                            if (j >= 0) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            j += 2;
                            if (j < 10) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            i++;
                            j = good_y - 2;
                            if (i < 10 && j >= 0) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            j++;
                            if (i < 10 && j >= 0 && j < 10) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            j++;
                            if (i < 10 && j >= 0 && j < 10) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            good_x = 0;
                            good_y = 0;
                            hit_ship_c = EMPTY;
                            c_hit = 0;
                        }
                        Game::Check();
                    }
                    else
                    {
                        cout << "You missed! End of your turn" << endl;
                        board_to_check[good_x][good_y - 1] = 'O';
                        Sleep(1500);
                        checked_coordinates.push_back(make_pair(good_x + 1, good_y));
                        if (c_hit == 2) {
                            good_x -= 1;
                        }
                        CurrentPlayer = PLAYER1;
                        if (c_hit == 1) {
                            direction = HORIZONTAL;
                        }
                    }
                }
                else if (good_x - 1 >= 1 && !if_checked(good_x - 1, good_y))
                {
                    cout << "Checking coordinates (" << good_x - 1 << " , " << good_y << ")" << endl;
                    if (board[good_x - 2][good_y - 1] == 'X') {
                        ++dynamic_cast<Comp&>(*AI);
                        c_hit++;
                        if (c_hit != 3) {
                            cout << "Good job you've hit the ship ! Your turn" << endl;
                            board_to_check[good_x - 2][good_y - 1] = 'X';
                            Sleep(1500);
                            checked_coordinates.push_back(make_pair(good_x - 1, good_y));
                            good_x -= 1;
                        }
                        else if (c_hit == 3) {
                            cout << "A three-masted ship was sunk! Your turn" << endl;
                            board_to_check[good_x - 2][good_y - 1] = 'X';
                            Sleep(1500);
                            checked_coordinates.push_back(make_pair(good_x - 1, good_y));
                            int i, j;
                            i = good_x - 3;
                            j = good_y - 2;
                            if (i >= 0 && j >= 0) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            j++;
                            if (i >= 0 && j >= 0 && j < 10) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            j++;
                            if (i >= 0 && j >= 0 && j < 10) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            i++;
                            j = good_y - 2;
                            if (j >= 0) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            j += 2;
                            if (j < 10) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            i++;
                            j = good_y - 2;
                            if (j >= 0) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            j += 2;
                            if (j < 10) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            i++;
                            j = good_y - 2;
                            if (j >= 0) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            j += 2;
                            if (j < 10) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            i++;
                            j = good_y - 2;
                            if (i < 10 && j >= 0) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            j++;
                            if (i < 10 && j >= 0 && j < 10) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            j++;
                            if (i < 10 && j >= 0 && j < 10) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }

                            good_x = 0;
                            good_y = 0;
                            hit_ship_c = EMPTY;
                            c_hit = 0;
                        }
                        Game::Check();
                    }
                    else {
                        cout << "You missed! End of your turn" << endl;
                        board_to_check[good_x - 2][good_y - 1] = 'O';
                        Sleep(1500);
                        checked_coordinates.push_back(make_pair(good_x - 1, good_y));
                        if (c_hit == 2) {
                            good_x += 1;
                        }
                        CurrentPlayer = PLAYER1;
                        if (c_hit == 1) {
                            direction = HORIZONTAL;
                        }
                    }
                }
            }
            else if (direction == HORIZONTAL) {

                if (!(good_y + 1 <= 10 && !if_checked(good_x, good_y + 1)) && !(good_y - 1 >= 1 && !if_checked(good_x, good_y - 1))) {
                    if (c_hit == 1)
                        direction = VERTICAL;
                    if (c_hit == 2) {
                        good_y -= 1;
                    }
                }

                if (good_y + 1 <= 10 && !if_checked(good_x, good_y + 1))
                {
                    cout << "Checking coordinates (" << good_x << " , " << good_y + 1 << ")" << endl;
                    if (board[good_x - 1][good_y] == 'X') {
                        ++dynamic_cast<Comp&>(*AI);
                        c_hit++;
                        if (c_hit != 3) {
                            cout << "Good job you've hit the ship ! Your turn" << endl;
                            board_to_check[good_x - 1][good_y] = 'X';
                            Sleep(1500);
                            checked_coordinates.push_back(make_pair(good_x, good_y + 1));
                            good_y += 1;
                        }
                        else if (c_hit == 3)
                        {
                            cout << "A three-masted ship was sunk! Your turn" << endl;
                            board_to_check[good_x - 1][good_y] = 'X';
                            Sleep(1500);
                            checked_coordinates.push_back(make_pair(good_x, good_y + 1));
                            int i, j;
                            i = good_x - 2;
                            j = good_y - 3;
                            if (i >= 0 && j >= 0) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            j++;
                            if (i >= 0) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            j++;
                            if (i >= 0) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            j++;
                            if (i >= 0) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            j++;
                            if (i >= 0 && j < 10) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            i++;
                            j = good_y - 3;
                            if (j >= 0) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            j += 4;
                            if (j < 10) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            i++;
                            j = good_y - 3;
                            if (i < 10 && j >= 0) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            j++;
                            if (i < 10 && j >= 0) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            j++;
                            if (i < 10 && j >= 0) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            j++;
                            if (i < 10 && j >= 0) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            j++;
                            if (i < 10 && j >= 0) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }

                            good_x = 0;
                            good_y = 0;
                            hit_ship_c = EMPTY;
                            c_hit = 0;
                        }
                        Game::Check();
                    }
                    else {
                        cout << "You missed! End of your turn" << endl;
                        board_to_check[good_x - 1][good_y] = 'O';
                        Sleep(1500);
                        checked_coordinates.push_back(make_pair(good_x, good_y + 1));
                        if (c_hit == 2) {
                            good_y -= 1;
                        }
                        CurrentPlayer = PLAYER1;
                        if (c_hit == 1) {
                            direction = VERTICAL;
                        }
                    }
                }
                else if (good_y - 1 >= 1 && !if_checked(good_x, good_y - 1))
                {
                    cout << "Checking coordinates (" << good_x << " , " << good_y - 1 << ")" << endl;
                    if (board[good_x - 1][good_y - 2]) {
                        ++dynamic_cast<Comp&>(*AI);
                        c_hit++;
                        if (c_hit != 3) {
                            cout << "Good job you've hit the ship ! Your turn" << endl;
                            board_to_check[good_x - 1][good_y - 2] = 'X';
                            Sleep(1500);
                            checked_coordinates.push_back(make_pair(good_x, good_y - 1));
                            good_y -= 1;
                        }
                        else if (c_hit == 3) {
                            cout << "A three-masted ship was sunk! Your turn" << endl;
                            board_to_check[good_x - 1][good_y - 2] = 'X';
                            Sleep(1500);
                            checked_coordinates.push_back(make_pair(good_x, good_y - 1));

                            int i, j;
                            i = good_x - 2;
                            j = good_y - 3;
                            if (i >= 0 && j >= 0) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            j++;
                            if (i >= 0) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            j++;
                            if (i >= 0) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            j++;
                            if (i >= 0) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            j++;
                            if (i >= 0 && j < 10) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            i++;
                            j = good_y - 3;
                            if (j >= 0) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            j += 4;
                            if (j < 10) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            i++;
                            j = good_y - 3;
                            if (i < 10 && j >= 0) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            j++;
                            if (i < 10 && j >= 0) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            j++;
                            if (i < 10 && j >= 0) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            j++;
                            if (i < 10 && j >= 0) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            j++;
                            if (i < 10 && j >= 0) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            good_x = 0;
                            good_y = 0;
                            hit_ship_c = EMPTY;
                            c_hit = 0;
                        }
                        Game::Check();
                    }
                    else
                    {
                        cout << "You missed! End of your turn" << endl;
                        board_to_check[good_x - 1][good_y - 2] = 'O';
                        Sleep(1500);
                        checked_coordinates.push_back(make_pair(good_x, good_y - 1));
                        if (c_hit == 2) {
                            good_y += 1;
                        }
                        CurrentPlayer = PLAYER1;
                        if (c_hit == 1) {
                            direction = VERTICAL;
                        }
                    }
                }
            }
        }
        else if (hit_ship_c == FOUR)
        {
            if (direction == VERTICAL)
            {
                if (!(good_x + 1 <= 10 && !if_checked(good_x + 1, good_y)) && !(good_x - 1 >= 1 && !if_checked(good_x - 1, good_y)))
                {
                    if (c_hit == 1)
                        direction = HORIZONTAL;
                    if (c_hit == 2) {
                        good_x -= 1;
                    }
                    if (c_hit == 3) {
                        good_x -= 2;
                    }
                }
                if (good_x + 1 <= 10 && !if_checked(good_x + 1, good_y))
                {
                    cout << "Checking coordinates (" << good_x + 1 << " , " << good_y << ")" << endl;
                    if (board[good_x][good_y - 1] == 'X') {
                        ++dynamic_cast<Comp&>(*AI);
                        c_hit++;
                        if (c_hit != 4) {
                            cout << "Good job you've hit the ship ! Your turn" << endl;
                            board_to_check[good_x][good_y - 1] = 'X';
                            Sleep(1500);
                            checked_coordinates.push_back(make_pair(good_x + 1, good_y));
                            good_x += 1;
                        }
                        else if (c_hit == 4) {
                            cout << "A four-masted ship was sunk! Your turn" << endl;
                            board_to_check[good_x][good_y - 1] = 'X';
                            checked_coordinates.push_back(make_pair(good_x + 1, good_y));
                            int i, j;
                            i = good_x - 4;
                            j = good_y - 2;
                            if (i >= 0 && j >= 0) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            j++;
                            if (i >= 0) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            j++;
                            if (i >= 0 && j < 10) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            i++;
                            j = good_y - 2;
                            if (j >= 0) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            j += 2;
                            if (j < 10) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            i++;
                            j = good_y - 2;
                            if (j >= 0) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            j += 2;
                            if (j < 10) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            i++;
                            j = good_y - 2;
                            if (j >= 0) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            j += 2;
                            if (j < 10) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            i++;
                            j = good_y - 2;
                            if (j >= 0) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            j += 2;
                            if (j < 10) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            i++;
                            j = good_y - 2;
                            if (i < 10 && j >= 0) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            j++;
                            if (i < 10) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            j++;
                            if (i < 10 && j < 10) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }

                            good_x = 0;
                            good_y = 0;
                            hit_ship_c = EMPTY;
                            c_hit = 0;

                        }
                        Game::Check();
                    }
                    else {
                        cout << "You missed! End of your turn" << endl;
                        board_to_check[good_x][good_y - 1] = 'O';
                        Sleep(1500);
                        checked_coordinates.push_back(make_pair(good_x + 1, good_y));
                        if (c_hit == 1) {
                            direction = HORIZONTAL;
                        }
                        if (c_hit == 2) {
                            good_x -= 1;
                        }
                        else if (c_hit == 3) {
                            good_x -= 2;
                        }
                        CurrentPlayer = PLAYER1;
                    }
                }
                else if (good_x - 1 >= 1 && !if_checked(good_x - 1, good_y))
                {
                    cout << "Checking coordinates (" << good_x - 1 << " , " << good_y << ")" << endl;
                    if (board[good_x - 2][good_y - 1] == 'X') {
                        ++dynamic_cast<Comp&>(*AI);
                        c_hit++;
                        if (c_hit != 4) {
                            cout << "Good job you've hit the ship ! Your turn" << endl;
                            board_to_check[good_x - 2][good_y - 1] = 'X';
                            Sleep(1500);
                            checked_coordinates.push_back(make_pair(good_x - 1, good_y));
                            good_x -= 1;
                        }
                        else if (c_hit == 4) {
                            cout << "A four-masted ship was sunk! Your turn" << endl;
                            board_to_check[good_x - 2][good_y - 1] = 'X';
                            checked_coordinates.push_back(make_pair(good_x - 1, good_y + 1));

                            int i, j;
                            i = good_x - 3;
                            j = good_y - 2;
                            if (i >= 0 && j >= 0) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            j++;
                            if (i >= 0) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            j++;
                            if (i >= 0 && j < 10) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            i++;
                            j = good_y - 2;
                            if (j >= 0) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            j += 2;
                            if (j < 10) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            i++;
                            j = good_y - 2;
                            if (j >= 0) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            j += 2;
                            if (j < 10) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            i++;
                            j = good_y - 2;
                            if (j >= 0) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            j += 2;
                            if (j < 10) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            i++;
                            j = good_y - 2;
                            if (j >= 0) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            j += 2;
                            if (j < 10) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            i++;
                            j = good_y - 2;
                            if (i < 10 && j >= 0) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            j++;
                            if (i < 10) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            j++;
                            if (i < 10 && j < 10) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }

                            good_x = 0;
                            good_y = 0;
                            hit_ship_c = EMPTY;
                            c_hit = 0;
                        }
                        Game::Check();
                    }
                    else
                    {
                        cout << "You missed! End of your turn" << endl;
                        board_to_check[good_x - 2][good_y - 1] = 'O';
                        Sleep(1500);
                        checked_coordinates.push_back(make_pair(good_x - 1, good_y));
                        if (c_hit == 1) {
                            direction = HORIZONTAL;
                        }
                        if (c_hit == 2) {
                            good_x += 1;
                        }
                        else if (c_hit == 3) {
                            good_x += 2;
                        }
                        CurrentPlayer = PLAYER1;
                    }
                }
            }
            else if (direction == HORIZONTAL)
            {

                if (!(good_y + 1 <= 10 && !if_checked(good_x, good_y + 1)) && !(good_y - 1 >= 1 && !if_checked(good_x, good_y - 1))) {

                    if (c_hit == 1)
                        direction = VERTICAL;
                    if (c_hit == 2) {
                        good_y -= 1;
                    }
                    if (c_hit == 3) {
                        good_y -= 2;
                    }
                }

                if (good_y + 1 <= 10 && !if_checked(good_x, good_y + 1))
                {
                    cout << "Checking coordinates (" << good_x << " , " << good_y + 1 << ")" << endl;
                    if (board[good_x - 1][good_y] == 'X') {
                        ++dynamic_cast<Comp&>(*AI);
                        c_hit++;
                        if (c_hit != 4) {
                            cout << "Good job you've hit the ship ! Your turn" << endl;
                            board_to_check[good_x - 1][good_y] = 'X';
                            Sleep(1500);
                            checked_coordinates.push_back(make_pair(good_x, good_y + 1));
                            good_y += 1;
                        }
                        else if (c_hit == 4) {
                            cout << "A four-masted ship was sunk! Your turn" << endl;
                            board_to_check[good_x - 1][good_y] = 'X';
                            Sleep(1500);
                            checked_coordinates.push_back(make_pair(good_x, good_y + 1));

                            int i, j;
                            i = good_x - 2;
                            j = good_y - 4;

                            if (i >= 0 && j >= 0) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            j++;
                            if (i >= 0) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            j++;
                            if (i >= 0) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            j++;
                            if (i >= 0) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            j++;
                            if (i >= 0) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            j++;
                            if (i >= 0 && j < 10) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            i++;
                            j = good_y - 4;
                            if (j >= 0) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            j += 5;
                            if (j < 10) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            i++;
                            j = good_y - 4;
                            if (i < 10 && j >= 0) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            j++;
                            if (i < 10) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            j++;
                            if (i < 10) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            j++;
                            if (i < 10) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            j++;
                            if (i < 10) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            j++;
                            if (i < 10 && j < 10) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }

                            good_x = 0;
                            good_y = 0;
                            hit_ship_c = EMPTY;
                            c_hit = 0;
                        }
                        Game::Check();
                    }
                    else {
                        cout << "You missed! End of your turn" << endl;
                        board_to_check[good_x - 1][good_y] = 'O';
                        Sleep(1500);
                        checked_coordinates.push_back(make_pair(good_x, good_y + 1));
                        if (c_hit == 1) {
                            direction = VERTICAL;
                        }
                        if (c_hit == 2) {
                            good_y -= 1;
                        }
                        else if (c_hit == 3) {
                            good_y -= 2;
                        }
                        CurrentPlayer = PLAYER1;
                    }
                }
                else if (good_y - 1 >= 1 && !if_checked(good_x, good_y - 1))
                {
                    cout << "Checking coordinates (" << good_x << " , " << good_y - 1 << ")" << endl;
                    if (board[good_x - 1][good_y - 2]) {
                        ++dynamic_cast<Comp&>(*AI);
                        c_hit++;
                        if (c_hit != 4) {
                            cout << "Good job you've hit the ship ! Your turn" << endl;
                            board_to_check[good_x - 1][good_y - 2] = 'X';
                            Sleep(1500);
                            checked_coordinates.push_back(make_pair(good_x, good_y - 1));
                            good_y -= 1;
                        }
                        else if (c_hit == 4) {
                            cout << "A four-masted ship was sunk! Your turn" << endl;
                            board_to_check[good_x - 1][good_y - 2] = 'X';
                            Sleep(1500);
                            checked_coordinates.push_back(make_pair(good_x, good_y - 1));
                            int i, j;
                            i = good_x - 2;
                            j = good_y - 3;
                            if (i >= 0 && j >= 0) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            j++;
                            if (i >= 0) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            j++;
                            if (i >= 0) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            j++;
                            if (i >= 0) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            j++;
                            if (i >= 0) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            j++;
                            if (i >= 0 && j < 10) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            i++;
                            j = good_y - 3;
                            if (j >= 0) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            j += 5;
                            if (j < 10) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            i++;
                            j = good_y - 3;
                            if (i < 10 && j >= 0) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            j++;
                            if (i < 10) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            j++;
                            if (i < 10) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            j++;
                            if (i < 10) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            j++;
                            if (i < 10) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            j++;
                            if (i < 10 && j < 10) {
                                board_to_check[i][j] = 'O';
                                checked_coordinates.push_back(make_pair(i + 1, j + 1));
                            }
                            good_x = 0;
                            good_y = 0;
                            hit_ship_c = EMPTY;
                            c_hit = 0;
                        }
                        Game::Check();
                    }
                    else
                    {
                        cout << "You missed! End of your turn" << endl;
                        board_to_check[good_x - 1][good_y - 2] = 'O';
                        Sleep(1500);
                        checked_coordinates.push_back(make_pair(good_x, good_y - 1));
                        if (c_hit == 2) {
                            good_y += 1;
                        }
                        if (c_hit == 3) {
                            good_y += 2;
                        }
                        CurrentPlayer = PLAYER1;
                        if (c_hit == 1) {
                            direction = VERTICAL;
                        }
                    }
                }
            }
        }
    }
}