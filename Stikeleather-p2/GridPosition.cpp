//Comments explaining all functions are in the Header file

#include "GridPosition.h"
#include <iostream>
#include <cctype>
using namespace std;

GridPosition::GridPosition(){
    node = '.';
}
GridPosition::GridPosition(char this_node){
    node = this_node;
}

void GridPosition::setNode(char this_node){
    node = this_node;
}

char GridPosition::getNode(){
    return node;
}

bool GridPosition::isChain(){
    if (node == '-' || node == '=' || node == '|' || node == 'H'){
        return true;
    }
    else{
        return false;
    }
}

GridPosition GridPosition::operator+(int newNum){
    if (isdigit(node)){
        int num = static_cast<int>(node);
        num += newNum;
        return GridPosition(static_cast<char>(num));
    }
    else{
        return node;
    }
}

GridPosition GridPosition::operator-(int newNum){
    if (isdigit(node)){
        int num = static_cast<int>(node);
        num -= newNum;
        return GridPosition(static_cast<char>(num));
    }
    else{
        return node;
    }
}

GridPosition& GridPosition::operator++(){ //Prefix - Returns incremented value
    if (isdigit(node)){
        node = static_cast<char>(node + 1);
    }
    return *this;   
}

GridPosition GridPosition::operator++(int){ //Postfix - return current node value, then increment.
    GridPosition temp = *this;
    if (isdigit(node)){
        node = static_cast<char>(node + 1);
    }
    return temp;
}

GridPosition& GridPosition::operator--(){ //Prefix - Returns incremented value
    if (isdigit(node)){
        node = static_cast<char>(node - 1);
    }
    return *this;  
}

GridPosition GridPosition::operator--(int){ //Postfix - return current node value, then increment.
    GridPosition temp = *this;
    if (isdigit(node)){
        node = static_cast<char>(node - 1);
    }
    return temp;
}