//Josh Stikeleather
//3/2/2025
//CPSC 1070 Spring 2025
//Chain Reaction: *Give a brief description of the game

#include <iostream>
#include "Board.h"
#include "GridPosition.h"
using namespace std;

int main(){
    
    cout<<"Welcome to CPSC 1070 Chain Reaction!"<<endl<<endl;
    cout<<"The goal is to connect all of the nodes into a single connected group"<<endl;
    cout<<"by creating a series of chains between the nodes. The number of chains"<<endl;
    cout<<"coming off of an node must match the number on that node."<<endl<<endl;
    cout<<"Enter the coordinates of the node you would like to connect and a direction."<<endl;
    cout<<"If there is already a chain, a second chain will be added. If there are"<<endl;
    cout<<"already two chains, the chains will be removed."<<endl<<endl;

    string my_file;
    fstream file;
    cout<<"Please enter the name of the file you would like to use: ";
    getline(cin, my_file);
    file.open(my_file);
    if (!file){ //Validates the users input file
        cout<<"Error opening file!"<<endl;
        file.close();
    }
    else{
        file.close();
        Board board(my_file);
        board.runGame();
    }
return 0;    
}