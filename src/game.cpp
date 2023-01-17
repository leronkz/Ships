#include "game.h"
#include "players.h"
#include <string>

using namespace std;

vector<pair<int, int>>checked_coordinates;
bool running = false;
int points_1 = 0;
int points_2 = 0;
char mode;

fstream file;

P* p1 = new Player;
P* p2 = new Player;
P* AI = new Comp;

PLAYERS CurrentPlayer;

void gotoxy(int x, int y)
{
    COORD c;
    c.X = x - 1;
    c.Y = y - 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void gotoxy(int x, double y)
{
    COORD c;
    c.X = x - 1;
    c.Y = y - 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void gotoxy(double x, int y)
{
    COORD c;
    c.X = x - 1;
    c.Y = y - 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void gotoxy(double x, double y)
{
    COORD c;
    c.X = x - 1;
    c.Y = y - 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}


void Game::Start()
{
    running = true;
    string n;

    checked_coordinates.clear();
    if (mode == '1') {
        cout << "1 PLAYER: Enter your name: ";
        getline(cin, n);
        p1->setName(n);
        p1->nr = 1;

        cout << "2 PLAYER: Enter your name: ";
        getline(cin, n);
        p2->setName(n);
        p2->nr = 2;

        CurrentPlayer = (rand() % 2 + 1 == 1 ? PLAYER1 : PLAYER2);

        p1->SetBoard();
        p2->SetBoard();

        system("cls");
        p1->SetShips();
        cout << "You've placed all the ships" << endl;
        Sleep(1000);
        p2->SetShips();
        cout << "You've placed all the ships" << endl;
        Sleep(1000);
    }
    else if (mode == '2')
    {
        cout << "Enter your name: ";
        getline(cin, n);
        p1->setName(n);
        p1->nr = 1;

        CurrentPlayer = PLAYER1;
        p1->SetBoard();
        AI->SetBoard();

        system("cls");
        p1->SetShips();
        cout << "You've placed all the ships" << endl;
        Sleep(1000);
        AI->SetShips();
    }


}
void Game::End()
{
    if (mode == '1')
        cout << "The game is over! Winner: " << (CurrentPlayer == PLAYER1 ? p1->printName() : p2->printName()) << endl;
    else if (mode == '2')
        cout << "The game is over! Winner: " << (CurrentPlayer == PLAYER1 ? p1->printName() : AI->printName()) << endl;
    Game::SaveToFile();
    Sleep(3000);

    checked_coordinates.clear();
    delete p1;
    delete p2;
    delete AI;
    exit(0);
}
void Game::Check()
{
    try {
        if (p1->points == 20 || p2->points == 20 || AI->points == 20) {
            Exceptions<ERRORS> exception(ER_WIN);
            throw exception;
        }
    }
    catch(Exceptions<ERRORS>e) {
        Exceptions<ERRORS>::manageException(reinterpret_cast<ERRORS &>(e));
    }
}
void Game::Draw()
{
    system("cls");
    if (mode == '1')
    {
        cout << p1->printName() << "'s board: " << endl;
        cout << endl;
        for (int i = 1; i <= 10; i++)
        {
            cout << i << " ";
        }
        cout << endl << endl;
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                cout << (*p1).board_to_check[i][j] << " ";
            }
            cout << " " << i + 1 << endl;
        }

        gotoxy(40, 1);
        cout << p2->printName() << "'s board: " << endl;
        gotoxy(40, 3);
        for (int i = 1; i < 10; i++)
        {
            cout << i << " ";
        }
        cout << endl << endl;
        gotoxy(40, 5);
        for (int i = 0; i < 10; i++)
        {
            gotoxy(40, 5 + i);
            for (int j = 0; j < 10; j++)
            {
                cout << (*p2).board_to_check[i][j] << " ";
            }
            cout << " " << i + 1 << endl;
        }
        cout << endl << endl;

        cout << "Current move: " << (CurrentPlayer == PLAYER1 ? p1->printName() : p2->printName()) << endl;
        if (CurrentPlayer == PLAYER1)
        {
            p1->Move(p2->board, p2->board_to_check, p2->board_s);
        }
        else
        {
            p2->Move(p1->board, p1->board_to_check, p1->board_s);
        }
    }
    else if (mode == '2')
    {
        cout << p1->printName() << "'s board: " << endl << endl;
        for (int i = 1; i <= 10; i++)
        {
            cout << i << " ";
        }
        cout << endl << endl;
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                cout << (*p1).board_to_check[i][j] << " ";
            }
            cout << " " << i + 1 << endl;
        }
        gotoxy(40, 1);
        cout << AI->printName() << "'s board: " << endl;
        gotoxy(40, 3);
        for (int i = 1; i <= 10; i++)
        {
            cout << i << " ";
        }
        cout << endl << endl;
        gotoxy(40, 5);
        for (int i = 0; i < 10; i++)
        {
            gotoxy(40, 5 + i);
            for (int j = 0; j < 10; j++)
            {
                cout << (*AI).board_to_check[i][j] << " ";
            }
            cout << " " << i + 1 << endl;
        }
        cout << endl << endl;
        cout << "Current move: " << (CurrentPlayer == PLAYER1 ? p1->printName() : AI->printName()) << endl;
        if (CurrentPlayer == PLAYER1)
        {
            p1->Move(AI->board, AI->board_to_check, AI->board_s);
        }
        else
        {
            AI->Move(p1->board, p1->board_to_check, p1->board_s);
        }
    }
}
void Game::SaveToFile()
{
    SYSTEMTIME st;
    GetSystemTime(&st);
    file.open("history.txt",  ios::out | ios::app);
    if (!file.good())
    {
        cout << "Can't open a file!" << endl;
        //tutaj obsługa wyjątków
    }
    else
    {
        if (mode == '1')
            file << "DATE: "<<st.wDay<<"."<<st.wMonth<<"."<<st.wYear<<" TIME: "<<st.wHour<<":"<<st.wMinute<<":"<<st.wSecond<<" GAME: " <<p1->printName()<<" vs "<<p2->printName()<<", Winner: " << (CurrentPlayer == PLAYER1 ? p1->printName() : p2->printName()) << endl;
        else if (mode == '2')
            file << "DATE: "<<st.wDay<<"."<<st.wMonth<<"."<<st.wYear<<" TIME: "<<st.wHour<<":"<<st.wMinute<<":"<<st.wSecond<<" GAME: "<<p1->printName()<<" vs " <<AI->printName() <<", Winner: " <<(CurrentPlayer == PLAYER1 ? p1->printName() : AI->printName()) << endl;
    }
    file.close();
}
void Game::LoadFromFile() {
        system("cls");
        file.open("history.txt",ios::in);
        if(!file.good())
        {
            cout<<"Can't open a file!"<<endl;
            //tutaj obsluga wyjatkow
        }
        cout<<"History of last games"<<endl;
        cout<<"------------------------------------"<<endl;
        string line;
        int i  = 1;
        while(!file.eof())
        {
            getline(file,line);
            cout<<i<<". "<<line<<endl;
            i++;
        }
        cout<<"------------------------------------"<<endl;
        cout<<"That's all"<<endl;
}

template<typename type>
void Exceptions<type>::manageException(Exceptions<type> exception) {
    switch(exception.typeOfException)
    {
        case ER_FIELD:
        {
            cout << "Wrong coordinates!" << endl;
        }break;
        case ER_BAD_PLACEMENT:
        {
            cout << "Bad ship positioning attempt!" << endl;
            cout << "Possible issues:" << endl;
            cout << "You tried to place a ship on the wrong number of fields or you tried to place a ship diagonally" << endl;
        }break;
        case ER_NR:
        {
            cout << "There is already a ship on these fields!" << endl;
        }break;
        case ER_NUMS:
        {
            cout << "Coordinates must be natural numbers!" << endl;
        }break;
        case ER_FIELD_CHECKED:
        {
            cout << "The field that you want to check is already checked!" << endl;
        }break;
        case ER_WIN:
        {
            Game::End();
        }break;
    }
}
