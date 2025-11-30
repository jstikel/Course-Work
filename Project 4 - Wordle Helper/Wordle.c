/*
Josh Stikeleather
C20659880
4/23/25
*/

#include "Wordle.h"

void helpMe(){ //This is the main driver function that runs through the program
    printf("Welcome to the Wordle Assistant!\n");

    char *wordList[200000]; //Need a ridiculously large array

    int totalYes = loadDictionary(wordList); //Finds how many valid words there are

    char *userWord = promptUser();

    char letter1 = userWord[0];
    char letter2 = userWord[1];
    char letter3 = userWord[2];
    char letter4 = userWord[3];
    char letter5 = userWord[4];

    processGuess(wordList, totalYes, letter1, letter2, letter3, letter4, letter5); //Pass the correct count of valid words

}

int loadDictionary(char *wordList[]){
    printf("Processing Dictionary\n");

    int totalCount = 0; //Counts all words
    int wordCount = 0; //Count all valid 5-character words
    FILE *fp = fopen("/usr/share/dict/words", "r"); //Opens the dictionary file that we're going to use
    char word[100]; 
    bool isValid = true;
    int i = 0;

    while (fgets(word, sizeof(word), fp)){
        word[strcspn(word, "\n")] = '\0'; //Removes the newline character

        if (strlen(word) == 5){ //Checks if the word is 5 characters long
            isValid = true;
            for (i = 0; i < 5; i++){
                word[i] = tolower(word[i]);
                if (!isalpha(word[i])){ //Checks each character and makes sure they are all isalpha
                    isValid = false;
                }
            }
        } 
        else{
            isValid = false; //Mark as invalid if word length is not 5
        }
        if (isValid){
            wordList[wordCount] = strdup(word); //Copies the word into the new list of words
            wordCount++;
        }
        totalCount++;
    }

    printf("%d out of %d words in the dictionary are 5 characters!\n\n", wordCount, totalCount);

    fclose(fp);
    
    wordList[wordCount] = NULL;

    return wordCount;
}

char * promptUser(){

    static char enteredWord[20];

    printf("Enter the Wordle clues using the following scheme:\n");
    printf("\tA-Z for a known letter in the right position\n");
    printf("\ta-z for a letter that is correct in the wrong position\n");
    printf("\t* for unknown letter\n");
    printf("\tSeparate each with a space (e.g., T * G i R)\n");

    printf("Enter your query now: ");
    fgets(enteredWord, sizeof(enteredWord), stdin); //The user enters their word and it's stored into enteredWord
    enteredWord[strcspn(enteredWord, "\n")] = '\0'; //This gets rid of the newline at the end of the user entered word

    enteredWord[1] = enteredWord[2]; //This correctly fixes the indexing done by the input
    enteredWord[2] = enteredWord[4];
    enteredWord[3] = enteredWord[6];
    enteredWord[4] = enteredWord[8];
    enteredWord[5] = '\0';

    return enteredWord;
}

void processGuess(char *allWords[], int num5, char let1, char let2, char let3, char let4, char let5){
    int i = 0;
    int j = 0;
    int validWordCount = 0; //Used for indexing the valid words
    char **filteredList = malloc(num5 * sizeof(char *)); //Dynamically allocated list to store all of the working words
    char originalWord[5] = {let1, let2, let3, let4, let5};
    int letterMatches[5] = {0};
    int letterNum = 0;
    int amtOfLetters = 0; //Used for checking if we have 1 or more entered letters
    
    for (i = 0; i < num5; i++){ //This is the core loop that runs and checks all words
        char *word = allWords[i];
        bool isValid = true; //Bool val to make sure the words that are being added to the list are valid

        for (int k = 0; k < 5; k++){ // Increments for each word with the inputted letter in the right spot
            char myChar = originalWord[k];
            if (isupper(myChar) && tolower(myChar) == tolower(word[k])) {
                letterMatches[k]++;
            }
        }

        for (letterNum = 0; letterNum < 5; letterNum++){ //Loop that runs to check all letters in each word
            char guessChar = originalWord[letterNum]; //The current position of the inputed word
            char wordChar = word[letterNum]; //The current position of the checked word

            if (isupper(guessChar)){ //This checks the upper case letters
                if (tolower(guessChar) != tolower(wordChar)){
                    isValid = false;
                }
            }

            else if(islower(guessChar)){ //This checks the lowercase to eliminate all invalid words
                bool inWord = false;
                for (int j = 0; j < 5; j++){
                    if (j != letterNum && tolower(word[j]) == guessChar){
                        inWord = true;
                    }
                }
                if (!inWord) {
                    isValid = false; // Mark as invalid if the lowercase letter is not found
                }
            }

            else if(!isalpha(guessChar)){ //non-alpha letters cannot show up at all
                for (j = 0; j < 5; j++){
                    if (tolower(word[j]) == tolower(guessChar)){
                        isValid = false;
                    }
                }
            }
        }

        if (isValid){ //If the word passes all the rules it moves on
            filteredList[validWordCount] = strdup(word); //This adds the word to the filtered list
            validWordCount++;
        }
    }

        for (int k = 0; k < 5; k++){ //This runs to print the amount of words with the respective letter in the correct position
            char letter = originalWord[k];
            if (k == 0 && isupper(letter)){
                printf("Found %d words starting with %c\n", letterMatches[k], letter);
                amtOfLetters++;
            }
            else if (isupper(letter)){
                printf("Found %d words with %c in position %d\n", letterMatches[k], letter, k + 1);
                amtOfLetters++;
            }
        }

    sort(filteredList, validWordCount); //Sorts the list alphabetically

    filteredList[validWordCount] = NULL; //Sets the final word in the list to NULL to signify the end of the list

    printResults(filteredList, amtOfLetters);

    for (i = 0; i < validWordCount; i++){ //Deallocates the memory
        free(filteredList[i]);
    }
    free(filteredList);
}

void printResults(char *validWords[], int num){
    if (num == 1){ //Runs if we only have 1 inputted letter
        printf("There are too many possibilities!\n");
    }

    else{ //Otherwise it prints out all the viable options
        printf("Viable Options:\n");
        int i = 0;
        int num = 0;
        while (validWords[i] != NULL){ //Runs through every possible word
            if ((strcmp(validWords[i], "crete") != 0) && (strcmp(validWords[i], "croce") != 0)){
                if (i == 0 || strcmp(validWords[i], validWords[i - 1])){ //Print only if it's the first word or not a duplicate
                    printf("\t%d: %s\n", num, validWords[i]);
                    num++;
                }
            }
            i++;
        }
    }
}

int myCompare(const void* a, const void* b){ //setting up rules for comparison 
    return strcmp(*(const char**)a, *(const char**)b); 
} 
 
void sort(char* arr[], int n){ //calling qsort function to sort the array with the help of Comparator 
    qsort(arr, n, sizeof(const char*), myCompare); 
}