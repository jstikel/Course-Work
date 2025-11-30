#include "Cipher.h"


Cipher::Cipher(){
    key1 = new char[5];
    strcpy(key1, "cpsc"); //This copies the string into the newly allocated key1
    key2 = new char[5];
    strcpy(key2, "cpsc");
    newKey = new char[5]; 
    setCipher(4, key1, key2); //Sets the key

}

Cipher::Cipher(int size, char* inputKey1){ //Overloaded constructor, takes in the size of the key, and the first key, assumes the second key is the same
    key1 = new char[size + 1];
    key2 = new char[size + 1];
    newKey = new char[size + 1];
    
    //Now copy the input key into key1
    strcpy(key1, inputKey1);

    //For now lets copy key2 as key1, we can change it later
    strcpy(key2, inputKey1);
    setCipher(strlen(key1), key1, key2);

}

Cipher::~Cipher(){ //Conditionals to avoid segfaults incase these are deleted somewhere else
    if (key1) delete[] key1;
    if (key2) delete[] key2;
    if (newKey) delete[] newKey;
}

void Cipher::setCipher(int size, char* inputKey1, char* inputKey2){ //Sets the cipher key newKey to the correct c-style string

    //Allocate memory for each of the keys
    key1 = new char[size + 1];
    key2 = new char[size + 1];
    newKey = new char[size + 1];

    //Correctly assign the inputkeys into arrays
    strcpy(key1, inputKey1);
    strcpy(key2, inputKey2);

    for (int i = 0; i < size; i++){ //Creates the newKey
        newKey[i] = (char)((((key1[i] - 'a' + 1) + (key2[i] - 'a' + 1)) % 26 + 'a' - 1));
    }
    newKey[size] = '\0'; //Used to signify the end of c-style strings

}

char* Cipher::getCipher(){
    return newKey;
}

string Cipher::encodeMessage(string input){
    Queue myQueue; //Make an empty queue

    for (size_t i = 0; i < strlen(newKey); i++){
        myQueue.enqueue(newKey[i]); //Enqueue all chars from the key
    }
    string message = ""; //This is the message that is going to be returned

    for (size_t i = 0; i < input.length(); i++){ //Runs through the entire entered string
        char keyChar; //Variable used to store the next char in the queue
        myQueue.dequeue(keyChar);
        char encodedChar = letterShift(input[i], keyChar, false); //Encodes the current char
        message += encodedChar;
        myQueue.enqueue(keyChar); //Puts the just used char back into the queue to be used again if needed
    }

    return message;
}

string Cipher::decodeMessage(string input){
    Queue myQueue; //Make an empty queue

    for (size_t i = 0; i < strlen(newKey); i++){
        myQueue.enqueue(newKey[i]); //Enqueue all chars from the key
    }
    string message = ""; //This is the message that is going to be returned

    for (size_t i = 0; i < input.length(); i++){ //Runs through the entire entered string
        char keyChar; //Variable used to store the next char in the queue
        myQueue.dequeue(keyChar);
        char decodedChar = letterShift(input[i], keyChar, true); //Decodes the current char
        message += decodedChar;
        myQueue.enqueue(keyChar); //Puts the just used char back into the queue to be used again if needed
    }

    return message;
}

char Cipher::letterShift(char l1, char l2, bool reverse){ 
    int temp;
    if (reverse){ //Runs if the user is trying to go backwards in the alphebet
        temp = (l1 + 1 - 'a') - (l2 + 1 - 'a'); //Corrects the indexing for the letters, then shifts them accordingly
        if (temp <= 0){
            temp += 26; //If the numbers go below 0, wraps back around to 26
        }
    }
    else{ //Runs if the user is trying to go forwards in the alphabet
        temp = (l1 + 1 - 'a') + (l2 + 1 - 'a'); //Similarly corrects the indexing for the letters and shifts them if needed
        if (temp > 26){
            temp -= 26; //If the numbers go above 25, shifts them back down to the correct position.
        }
    }
    return static_cast<char>(temp - 1 + 'a');
}