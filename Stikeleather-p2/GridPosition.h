#ifndef GRIDPOS_H
#define GRIDPOS_H
#include <iostream>
using namespace std;

class GridPosition{
public:
    GridPosition(); //Default constructor, sets the node char to an empty space (‘.’)
    GridPosition(char); //Parameterized constructor, sets the node char to the passed character.
    void setNode(char); //Sets the node char to the passed character.
    char getNode(); //Returns the node char.
    bool isChain(); //Returns true if the node char is ‘-’, ‘=’, ‘|’, or ‘H’ and false otherwise.
    GridPosition operator+(int); //If the node char is a number, increases it by the passed int but returns a new GridPosition instead of modifying the current one.
    GridPosition operator-(int); //If the node char is a number, decreases it by the passed int but returns a new GridPosition instead of modifying the current one.
    GridPosition& operator++(void); //prefix // If the node char is a number, increases it by one.
    GridPosition operator++(int); //postfix // If the node char is a number, increases it by one but returns the GridPosition with the original char.
    GridPosition& operator--(void); //prefix // If the node char is a number, decreases it by one.
    GridPosition operator--(int); //postfix // If the node char is a number, decreases it by one but returns the GridPosition with the original char.
private:
    char node;
};
#endif