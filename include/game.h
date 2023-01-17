#pragma once
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <exception>
#define SIZE 10

using namespace std;

enum ERRORS {ER_FIELD,ER_FIELD_CHECKED,ER_WIN,ER_NR,ER_BAD_PLACEMENT,ER_NUMS};

extern bool running;
extern char mode;
/**
 *
 * @param x x-coordinate
 * @param y y-coordinate
 * Function places the cursor on the console screen at specified point(x,y)
 */
void gotoxy(int x, int y);
/**
 *
 * @param x x-coordinate
 * @param y y-coordinate
 * Function places the cursor on the console screen at specified point(x,y)
 */
void gotoxy(double x, double y);
/**
 *
 * @param x x-coordinate
 * @param y y-coordinate
 * Function places the cursor on the console screen at specified point(x,y)
 */
void gotoxy(int x, double y);
/**
 *
 * @param x x-coordinate
 * @param y y-coordinate
 * Function places the cursor on the console screen at specified point(x,y)
 */
void gotoxy(double x, int y);

template<typename type>class Exceptions
{
public:
    type typeOfException;
public:
    /**
     * Constructor
     */
    Exceptions();
    /**
     *
     * @param exception
     * Constructor: sets the typeOfException
     */
    Exceptions(type exception){
        typeOfException = exception;
    }
    /**
     *
     * @param exception
     * Checks the type of exception and prints the right message
     */
    static void manageException(Exceptions<type> exception);
};
class Game {

public:
    /**
     * Starts the game
     */
    static void Start();
    /**
     * Ends the game
     */
    static void End();
    /**
     * Checks if the game is over
     */
    static void Check();
    /**
     * Draws boards of two players
     */
    static void Draw();
    /**
     * Saves the result of the game to the file
     */
    static void SaveToFile();
    /**
     * Prints the results of the played games
     */
    static void LoadFromFile();
};
