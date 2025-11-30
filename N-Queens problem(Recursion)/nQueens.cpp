/*
 * Name: Josh Stikeleather
 * Date Submitted: 11/16/2025
 * Lab Section: 003
 * Assignment Name: Using Recursion to solve the N-Queens problem
 */

#include <iostream>
#include <vector>

using namespace std;

int nQueens(int);
void placeRow(int);

 //Using static variables so that we can access them in multiple functions, and makes recursion easier
static vector<bool> colUsed; //Tracks which columns currently have queens in them
static vector<bool> rightDiagonal; //Tracks the "/" diagonal
static vector<bool> leftDiagonal; //Tracks the "\" diagonal
static int N;
static int localCount; //Counts the solutions for the current recursive branch

//Uses recursion to count how many solutions there are for
//placing n queens on an nxn chess board
int nQueens(int n)
{
    //Assigning values to our global variables
    N = n;

     //Initalize all of our values to false because nothing is occupied yet
    colUsed.assign(n, false);
    rightDiagonal.assign(n*2, false); 
    leftDiagonal.assign(n*2, false);

    int totalSolutions = 0;
    int half = n / 2; //Used for symmetry optimization

    //We check the first half of columns to cut our runtime in half, does NOT account for middle row if n is odd
    for (int col = 0; col < half; col++){
        colUsed[col] = rightDiagonal[n - col] = leftDiagonal[col] = true; //This places our first queen
        
        localCount = 0; //We reset the localCount before each branch begins
        placeRow(1); 
        
        totalSolutions += 2 * localCount; //Multiply by 2 to account for symmetry
        colUsed[col] = rightDiagonal[n - col] = leftDiagonal[col] = false; //Then we backtrack
    }

    //This runs if n is odd, so we can check our middle row
    if (n % 2 == 1){
        colUsed[half] = rightDiagonal[n - half] = leftDiagonal[half] = true; //Places a queen in the middle column

        localCount = 0;
        placeRow(1); //Continue the recurusive search

        totalSolutions += localCount;
        colUsed[half] = rightDiagonal[n - half] = leftDiagonal[half] = false; //Then we backtrack
    }

    return totalSolutions;
}

void placeRow(int row){
    if (row == N){ //Base case, all rows filled and we found a valid solution
        localCount++;
        return;
    }

    //Here we try to place a queen in each column of the new row
    for (int col = 0; col < N; col++){
        if (colUsed[col] == true){ //If the column has already been used
            continue;
        }
        if (rightDiagonal[row - col + N] == true){ //If the "/" diagonal has already been used
            continue;
        }
        if (leftDiagonal[row + col] == true){ //If the "\" diagonal has already been used
            continue;
        };

        colUsed[col] = rightDiagonal[row - col + N] = leftDiagonal[row + col] = true; //Place queen and mark columns and diagonals as occupied

        placeRow(row + 1); //Recurse to check the next row

        colUsed[col] = rightDiagonal[row - col + N] = leftDiagonal[row + col] = false; //Then we backtrack
    }
}

int main()
{
    cout << "1: " << nQueens(1) << endl;
    cout << "2: " << nQueens(2) << endl;
    cout << "3: " << nQueens(3) << endl;
    cout << "4: " << nQueens(4) << endl;
    cout << "5: " << nQueens(5) << endl;
    cout << "6: " << nQueens(6) << endl;
    cout << "7: " << nQueens(7) << endl;
    cout << "8: " << nQueens(8) << endl;
    cout << "9: " << nQueens(9) << endl;
    cout << "10: " << nQueens(10) << endl;
    cout << "11: " << nQueens(11) << endl;
    cout << "12: " << nQueens(12) << endl;
    return 0;
}
