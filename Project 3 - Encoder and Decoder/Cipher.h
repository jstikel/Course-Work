#ifndef CIPHER_H
#define CIPHER_H
#include "Queue.h"
#include <iostream>
#include <memory>
#include <cstdlib>
#include <string>
#include <cstring>
using namespace std;

class Cipher{
    public:
        Cipher();
        Cipher(int, char*);
        ~Cipher();
        void setCipher(int, char*, char*);
        char * getCipher();
        string encodeMessage(string input);
        string decodeMessage(string input);
        static char letterShift(char l1, char l2, bool reverse);
    private:
        char *key1 = nullptr;
        char *key2 = nullptr;
        char *newKey = nullptr;
};

#endif