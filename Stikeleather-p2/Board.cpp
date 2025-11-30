#include "Board.h"
#include "GridPosition.h"
#include <iostream>
#include <string>
#include <fstream>
#include <array>
#include <algorithm>
#include <limits>

Board::Board(){ //Dynamically allocates an empty board
    board = new GridPosition*[10];
    for (int i = 0; i < 10; i++){
        board[i] = new GridPosition[10];
    }
    for (int row = 0; row < 10; row++){ //First loop runs through and sets all numbers
        for (int col = 0; col < 10; col++){
            if (board[row][col].getNode() == '0'){
                int val = countChains(row, col);
                board[row][col].setNode('0' + val);
            }
        }
    }
    for (int row = 0; row < 10; row++){ //Second loop runs through and clears out the chains for the user to play
        for (int col = 0; col < 10; col++){
            if (board[row][col].isChain()){
                board[row][col].setNode('.');
            }
        }
    }
}
Board::Board(string file_input){ //Dynamically allocates the board from the .txt file
    board = new GridPosition*[10];
    for (int i = 0; i < 10; i++){
        board[i] = new GridPosition[10];
    }
    string my_file = file_input;
    ifstream file;
    string line;
    file.open(my_file);
    int row = 0;
    while (getline(file, line)){
        for (int c = 0; c < 10; c++){
            board[row][c].setNode(line[c]);
        }
        row += 1;
    }
    file.close();
    for (int row = 0; row < 10; row++){ //First loop runs through and sets all numbers
        for (int col = 0; col < 10; col++){
            if (board[row][col].getNode() == '0'){
                int val = countChains(row, col);
                board[row][col].setNode('0' + val);
            }
        }
    }
    for (int row = 0; row < 10; row++){ //Second loop runs through and clears out the chains for the user to play
        for (int col = 0; col < 10; col++){
            if (board[row][col].isChain()){
                board[row][col].setNode('.');
            }
        }
    }
}

bool Board::checkWin(){
    int connected_sum = 0;

    for (int row = 0; row < 10; row++){
        for (int col = 0; col < 10; col++){
            if (isdigit(board[row][col].getNode())){
                connected_sum = 0;
                if ((row + 1) < 10){
                    if (board[row + 1][col].getNode() == 'H' || board[row + 1][col].getNode() == '|'){
                        connected_sum += chainValue(board[row + 1][col].getNode());
                    }
                }
                if ((row - 1) >= 0){
                    if (board[row - 1][col].getNode() == 'H' || board[row - 1][col].getNode() == '|'){
                        connected_sum += chainValue(board[row - 1][col].getNode());
                    }
                }
                if ((col + 1) < 10){
                    if (board[row][col + 1].getNode() == '-' || board[row][col + 1].getNode() == '='){
                        connected_sum += chainValue(board[row][col + 1].getNode());
                    }
                }
                if ((col - 1) >= 0){
                    if (board[row][col - 1].getNode() == '-' || board[row][col - 1].getNode() == '='){
                        connected_sum += chainValue(board[row][col - 1].getNode());
                    }
                }

                if (connected_sum != (board[row][col].getNode() - '0')){
                    return false;
                }
            }
        }
    }
    return true;
}

void Board::runGame(){
    string input;
    bool win = false;
    printBoard();
    while (win == false){
        cout<<"Enter a row, a column, a space, and a cardinal direction (e.g. AK n): ";

        getline(cin, input);
        cout<<endl;
        bool yes = validChain(input);
        while (yes == false){
            cout<<"Enter a row, a column, a space, and a cardinal direction (e.g. AK n): ";
            getline(cin, input);
            cout<<endl;
            yes = validChain(input);
        }
        placeChains(input);
        printBoard();
        win = checkWin(); 
    }
    cout<<"Congratulations! You have connected all the nodes!"<<endl;
}

int Board::countChains(int row, int col){
    int sum = 0; //These are for checking the directions from the respective position
    
    if ((col - 1) >= 0){
        char left_node = board[row][col - 1].getNode();
        if (left_node == '-' || left_node == '='){
            sum += chainValue(left_node);
        }
    }
    if ((col + 1) < 10){
        char right_node = board[row][col + 1].getNode();
        if (right_node == '-' || right_node == '='){
            sum += chainValue(right_node);
        }
    }
    if ((row - 1) >= 0){
        char upper_node = board[row - 1][col].getNode();
        if (upper_node == '|' || upper_node == 'H'){
            sum += chainValue(upper_node);
        }
    }
    if ((row + 1) < 10){
        char lower_node = board[row + 1][col].getNode();
        if (lower_node == '|' || lower_node == 'H'){
            sum += chainValue(lower_node);
        }
    }

    return sum;
}

int Board::chainValue(char this_node){
    if (this_node == '-' || this_node == '|'){
        return 1;
    }
    else if (this_node == '=' || this_node == 'H'){
        return 2;
    }
    else{
        return 0;
    }
}

bool Board::validChain(string input){
    if (input.length() != 4){ //Insures the input is the correct amount of spaces
        cout<<"Invalid input. Too many or too few characters."<<endl;
        return false;
    }
    if (isupper(input[0]) == false){
        input[0] = toupper(input[0]);
    }
    if (isupper(input[1]) == false){
        input[1] = toupper(input[1]);
    }
    //Checks if the user input a valid row/column
    if (find(begin(rowArray), end(rowArray), input[0]) == end(rowArray) || find(begin(columnArray), end(columnArray), input[1]) == end(columnArray)){
        cout<<"Invalid input. Row must be A-J and column must be K-T."<<endl;
        return false;
    } //Checks to make sure that there's a space between the direction and the coordinates
    if (input[2] != ' ' || find(begin(directionArray), end(directionArray), input[3]) == end(directionArray)){
        cout<<"Invalid input. Direction must be n, e, s, or w and there must be a space between the column and direction."<<endl;
        return false;
    }
    char row = input[0];
    char col = input[1];
    char dir = input[3];
    int row_val = -1;
    int col_val = -1;
    for (int num = 0; num < 10; num++){ //This is used to assign the input values to their respective positions on the board
        if (row == rowArray[num]){
            row_val = num;
        }
        if (col == columnArray[num]){
            col_val = num;
        }
    }
    //Validates the position is a node, and not empty
    if(board[row_val][col_val].getNode() == '.' || row_val < 0 || row_val >= 10 || col_val < 0 || col_val >= 10){
        cout<<"Invalid input. There is no node at that location."<<endl;
        return false;
    }
    //Following block of code checks all 4 directions and validates that it doens't go off the board or intersect another chain
    if(dir == 'n' || dir == 's'){
        if (dir == 'n') row_val -= 1;
        if (dir == 's') row_val += 1;//This sets the value of the row to the next position north/south
        char next_row = board[row_val][col_val].getNode();
        for(int i = 0; i < 10; i++){
            if (row_val < 0 || row_val >= 10){
                cout<<"Invalid input. That path is blocked or goes off the board."<<endl;
                return false;
            }
            next_row = board[row_val][col_val].getNode(); //Set to the value of the next value north/south
            if (board[row_val][col_val].getNode() == '-' || board[row_val][col_val].getNode() == '='){
                cout<<"Invalid input. That path is blocked or goes off the board."<<endl;
                return false;
            }
            else if (isdigit(next_row)){
                return true;
            }
            else if (next_row == '.'){
                if (dir == 'n') row_val -= 1;
                if (dir == 's') row_val += 1;
            }
            else {
                if (dir == 'n') row_val -= 1;
                if (dir == 's') row_val += 1;
            }
        }
    }

    if(dir == 'e' || dir == 'w'){
        if (dir == 'e') col_val += 1;
        if (dir == 'w') col_val -= 1; //This sets the value of the row to the next position east/west
        char next_col_e = board[row_val][col_val].getNode();
        for(int i = 0; i < 10; i++){ //This for loop runs through each column and checks to make sure the next location is valid
            if (col_val >= 10 || col_val < 0){
                cout<<"Invalid input. That path is blocked or goes off the board."<<endl;
                return false;
            }
            next_col_e = board[row_val][col_val].getNode(); //Set to the value of the next node east/west
            if (board[row_val][col_val].getNode() == '|' || board[row_val][col_val].getNode() == 'H'){
                cout<<"Invalid input. That path is blocked or goes off the board."<<endl;
                return false;
            }
            else if (isdigit(next_col_e)){
                return true;
            }
            else if (next_col_e == '.'){
                if (dir == 'e') col_val += 1;
                if (dir == 'w') col_val -= 1;
            }
            else {
                if (dir == 'e') col_val += 1;
                if (dir == 'w') col_val -= 1;
            }
        }
    }

    return false;
}

void Board::placeChains(string input){
    if (isupper(input[0]) == false){
        input[0] = toupper(input[0]);
    }
    if (isupper(input[1]) == false){
        input[1] = toupper(input[1]);
    }
    char row = input[0]; //Initalizing all variables that we're going to need
    char col = input[1];
    char dir = input[3];
    int row_val = -1;
    int col_val = -1;
    for (int num = 0; num < 10; num++){ //This is used to assign the input values to their respective positions on the board
        if (row == rowArray[num]){
            row_val = num;
        }
        if (col == columnArray[num]){
            col_val = num;
        }
    }

    if (dir == 'n' || dir == 's'){
        if (dir == 'n') row_val -= 1; //This sets the value of the row to the next position
        if (dir == 's') row_val += 1;
        char next_spot = board[row_val][col_val].getNode();
        for(int i = 0; i < 10; i++){
            next_spot = board[row_val][col_val].getNode();
            if (next_spot == '.'){
                board[row_val][col_val].setNode('|');
                if (dir == 'n') row_val -= 1;
                if (dir == 's') row_val += 1;
            }
            else if (next_spot == '|'){
                board[row_val][col_val].setNode('H');
                if (dir == 'n') row_val -= 1;
                if (dir == 's') row_val += 1;
            }
            else if (next_spot == 'H'){
                board[row_val][col_val].setNode('.');
                if (dir == 'n') row_val -= 1;
                if (dir == 's') row_val += 1;
            }
            else if (isdigit(next_spot)){
                i = 10; //This ends the loop and stops setting the chains
            }
        }
    }

    if (dir == 'e' || dir == 'w'){
        if (dir == 'e') col_val += 1;
        if (dir == 'w') col_val -= 1;
        char next_spot = board[row_val][col_val].getNode();
        for (int i = 0; i < 10; i++){
            next_spot = board[row_val][col_val].getNode();
            if (next_spot == '.'){
                board[row_val][col_val].setNode('-');
                if (dir == 'w') col_val -= 1;
                if (dir == 'e') col_val += 1;
            }
            else if (next_spot == '-'){
                board[row_val][col_val].setNode('=');
                if (dir == 'w') col_val -= 1;
                if (dir == 'e') col_val += 1;
            }
            else if (next_spot == '='){
                board[row_val][col_val].setNode('.');
                if (dir == 'w') col_val -= 1;
                if (dir == 'e') col_val += 1;
            }
            else if (isdigit(next_spot)){
                i = 10; //This ends the loop and stops setting the chains
            }
        }
    }
}

void Board::printBoard(){

    cout<<endl;
    cout<<"    ";
    for (int i = 0; i < 10; i++){
        if (i != 9){
            cout<<columnArray[i]<<" ";
        }
        else{
            cout<<columnArray[i]<<endl;
        }
    }
    cout<<"  ---------------------"<<endl;

    for (int row = 0; row < 10; row++){ //Had a slight mix up with the values of rowArray and columnArray but the logic works fine even if the counters have weird names
        cout<<rowArray[row]<<" | ";
        for (int col = 0; col < 10; col++){
            if (col != 9){
                cout<<board[row][col].getNode()<<' ';
            }
            else{
                cout<<board[row][col].getNode();
            }
        }
        cout<<endl;
    }
    cout<<endl;
}

char Board::rowArray[10] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
char Board::columnArray[10] = {'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T'};
char Board::directionArray[4] = {'n', 'e', 's', 'w'};

Board::~Board(){
    for (int i = 0; i < 10; i++){
        delete[] board[i];
    }
    delete[] board;
}

