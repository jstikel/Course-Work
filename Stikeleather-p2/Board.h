#ifndef BOARD_H
#define BOARD_H
#include "GridPosition.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

class Board{

public:
    Board(); //Default constructor
    Board(string myFile); //Constructor that opens the file and dynamically allocates the memory for that board
    void runGame(); //Runs the game in a loop until the player has won
    int countChains(int, int); //Function to count and return how many chains are connected to a node as helper for setting up the board after reading it from the file
    int chainValue(char); //Helper function for countChains to clean up code
    bool checkWin(); //This function uses countChains to determine whether the number of chains attached to every
                    //node on the board matches the number of that node, returning true if that’s the case and false otherwise.
    bool validChain(string input); //This function passes the user input as a string and returns false if placing chains based on that
                                   //input would go off the board without hitting a node or cross over an existing chain, otherwise it returns true.
    void placeChains(string input); //Function to take the user input as a string and place chains onto the board accordingly.
    void printBoard(); //Function to print the board with its labels.
    ~Board();
    
private:
    GridPosition** board;
    static char rowArray[10]; //Helper arrays to clean up the printBoard function
    static char columnArray[10];
    static char directionArray[4]; //Helper array for validChain
};

#endif