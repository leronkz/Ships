#include <iostream>
#include "game.h"
#include "players.h"
/**
 * Gives help and information about the program
 */
void help()
{
    cout << "Simple game - ships" << endl;
    cout << "There're two available modes: " << endl;
    cout << "1 - Player vs Player" << endl;
    cout << "2 - Player vs Computer" << endl;
    cout << "How to place ships:" << endl;
    cout << "1.You need to enter the coordinates of the starting point" << endl;
    cout << "2.You need to eneter the coordinates of the ending point " << endl;
    cout << "If you place a four-masted ship you need to remeber not to enter the wrong ending point for example" << endl;
    cout << "the distance between the starting point or ending point is greater or less then the size of the ship" << endl;
    cout << "When it's your turn you need to enter the coordinates of the field that you want to check" << endl;
}
int main(int argc, char* argv[])
{
    srand(time(NULL));
    cout << "SHIPS" << endl;
    cout << "Chosen game mode: " << argv[1] << endl;
    if (*argv[1] == '1') {
        cout << "Player vs Player" << endl;
        mode = '1';
    }
    else if (*argv[1] == '2') {
        cout << "Player vs Computer" << endl;
        mode = '2';
    }
    else if(*argv[1]=='3')
    {
        Game::LoadFromFile();
        exit(0);
    }
    else
    {
        help();
    }
    Sleep(1000);
    system("cls");
    Game::Start();
    while (running)
        Game::Draw();
    Game::End();
    return 0;
}