#pragma once
#include <iostream>
#include <vector>
#include <Windows.h>

#define SIZE 10;

using namespace std;
class P;
enum SHIPS { EMPTY, ONE, TWO, THREE, FOUR };
enum PLAYERS { PLAYER1, PLAYER2, COMPUTER };
enum DIRECTION { VERTICAL, HORIZONTAL, NONE };
/**
 *
 * @param x_p   the x-coordinate of the first point
 * @param y_p   the y-coordinate of the first point
 * @param x_k    the x-coordinate of the second point
 * @param y_k   the y-coordinate of the second point
 * @param k     length of the ship
 * @param board player's board
 * @return true if the ship can be placed on given area or false if cannot
 */
bool check(int x_p, int y_p, int x_k, int y_k, int k, char** board);
/**
 *
 * @param x x-coordinate of the point
 * @param y y-coordinate of the point
 * @return  true if the point has been already checked or false if not
 */
bool if_checked(int x, int y);
/**
 *
 * @param player The player that calls the function
 * @param length length of the ship that is being placed
 * @param s the type of the ship that is being placed
 */
void autoset(P* player, int length, SHIPS s);

class P {
public:
    string nick;
    int nr;
    char** board;
    char** board_to_check;
    SHIPS** board_s;
    int points;
public:
    virtual void SetBoard() = 0;
    virtual void SetShips() = 0;
    virtual void SetShip(int length,SHIPS s)=0;
    virtual void Move(char** board, char** board_to_check, SHIPS** board_s)=0;
    /**
     *
     * @param n nickname
     * Sets the nickname of the player
     */
    void setName(string n) { nick = n; }
    /**
     *
     * @return returns the name of the player
     */
    string printName() const { return nick; }
};

class Player : public P
{
public:
    /**
     * Constructor
     * @param n nickname
     */
    Player(string n);
    /**
     * Constructor
     */
    Player();
    /**
     * Desctructor
     */
    ~Player();
    /**
     * Sets the board of the player
     */
    void SetBoard();
    /**
     * Sets the ships on player's board
     */
    void SetShips();
    /**
     *
     * @param length the length of the ship
     * @param s the type of ship
     */
    void SetShip(int length,SHIPS s);
    /**
     *
     * @param board enemy's board with placed ships
     * @param board_to_check enemy's board with placed ships that are hidden
     * @param board_s enemy's board with types of ships
     * The player checks if he guessed the right point
     */
    void Move(char** board, char** board_to_check, SHIPS** board_s);
    /**
     * Overloading operator ++
     */
    void operator++();
    friend void autoset(P* player, int length, SHIPS s);
};

class Comp : public P
{
public:
    /**
     * Constructor
     * @param n nickname
     */
    Comp(string n);
    /**
     * Constructor
     */
    Comp();
    /**
     * Destructor
     */
    ~Comp();
    /**
     * Sets the board of the player
     */
    void SetBoard();
    /**
     * Sets the ships on player's board
     */
    void SetShips();
    /**
   *
   * @param length the length of the ship
   * @param s the type of ship
   */
    void SetShip(int length,SHIPS s);
    /**
    * Overloading operator ++
    */
    void operator++();
    /**
     *
     * @param board enemy's board with placed ships
     * @param board_to_check enemy's board with placed ships that are hidden
     * @param board_s enemy's board with types of ships
     * Player checks if he guessed the right point
     */
    void Move(char** board, char** board_to_check, SHIPS** board_s);
};

void autoset(P* player,int length,SHIPS s);