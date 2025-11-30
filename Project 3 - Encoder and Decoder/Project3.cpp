/*
Josh Stikeleather
04/09/25
References: GeeksforGeeks, copilot for errors, and programiz
This is an Encoder and Decoder for when you need to hide your texts from your parents! This utilyzes C-style strings and pointers to directly encode and decode messages.
*/

#include <iostream>
#include <vector>
#include "Queue.h"
#include "Cipher.h"
using namespace std;

void runMenu();

int main(){
   runMenu(); //Simple driver function, probably useless but makes the main look cleaner
return 0;
}

void runMenu(){
   string strKey1 = "";
   string strKey2 = "";

   cout<<"Type in the first word to use as the key: ";
   getline(cin, strKey1);
   cout<<"Type in the second word to use as the key: ";
   getline(cin, strKey2);

   //This allocates new space for the two keys and converts the strings into c-style strings
   char *key1 = new char[strKey1.length() + 1]; 
   char *key2 = new char[strKey1.length() + 1];
   strcpy(key1, strKey1.c_str());
   strcpy(key2, strKey2.c_str());

   int j = 0; //This block runs through the code and gets rid of spaces and decapitalizes all letters
   for (int i = 0; i < static_cast<int>(strKey1.length()); i++){
      if (isalpha(key1[i])){
         key1[j++] = tolower(key1[i]);
      }
   }

   key1[j] = '\0'; //Signifies the end of the c-style string

   j = 0; //This block runs through the code and gets rid of spaces and decapitalizes all letters
   for (int i = 0; i < static_cast<int>(strKey1.length()); i++){
      if (isalpha(key2[i])){
         key2[j++] = tolower(key2[i]);
      }
   }

   key2[j] = '\0';//Signifies the end of the c-style string

   cout<<endl<<"Keys: "<<key1<<" and "<<key2<<endl;

   Cipher myCipher;
   myCipher.setCipher(strlen(key1), key1, key2);

   cout<<"New Key: "<<myCipher.getCipher()<<endl;
   bool ciphering = true;
   char choice = ' ';

   while (ciphering){ //Simple while loop that runs until the user decides to stop
      cout<<"[e] encode with this key"<<endl;
      cout<<"[d] decode with this key"<<endl;
      cout<<"[q] quit"<<endl;
      cin>>choice;
      if (tolower(choice) == 'e'){
         string word = "";
         cout<<"Enter what to encode: ";
         cin>>word;
         cout<<"result: "<<myCipher.encodeMessage(word)<<endl<<endl;
      }
      else if (tolower(choice) == 'd'){
         string word = "";
         cout<<"Enter what to decode: ";
         cin>>word;
         cout<<"result: "<<myCipher.decodeMessage(word)<<endl<<endl;
      }
      else{
         ciphering = false;
      }
   }
}