/*
Josh Stikeleather
C20659880
4/23/25
*/

#ifndef WORDLE_H
#define WORDLE_H
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>

int loadDictionary(char *[]); //Finds the amount of valid words in the dictionary
char * promptUser(); //This prompts the user for the information they have and returns it back to the driver function
void processGuess(char *[], int num5, char, char, char, char, char); //Runs and finds however 
                                                                    //many words there are that are valid for each character
void printResults(char *[], int); //Finds all options for words that match every correct and misplaced letter
void helpMe(); //Essentially the driver file
int myCompare(const void*, const void* ); //A comparetor function for sort **THIS IS FROM GEEKSFORGEEKS**
void sort(char* [], int); //The function to acutally sort the array alphabetically **THIS IS FROM GEEKSFORGEEKS**

#endif