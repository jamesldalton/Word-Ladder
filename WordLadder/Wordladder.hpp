//
//  Wordladder.hpp
//  WordLadder
//
//  Created by James on 11/11/15.
//  Copyright © 2015 James Dalton. All rights reserved.
//

#ifndef Wordladder_hpp
#define Wordladder_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include "Graph.hpp"

using namespace std;

class Wordladder {
private:
    // variables
    string word1;       // var to hold one of the words
    string word2;       // var to hold the other word
    clock_t t;          // var to hold the number of clock ticks
    ifstream wordsFile; // object for reading dictionary
    
    vector<string> dictionary; // contains the words from the dictionary being used
    vector<string>::iterator dictionaryIt; // iterator for dictionary
    
    // methods
    void loadWords();   // load words from file
    void getWords();    // prompt user to give two four letters words
    int checkWords();   // check both words are four letters and long and inside the dictionary
    void solver();       // begin solver
    
    clock_t beginCounter();// begins the clock
    clock_t stopCounter(); // stop the clock
    
public:
    Wordladder();
    ~Wordladder();
    void start();
};

#endif /* Wordladder_hpp */
