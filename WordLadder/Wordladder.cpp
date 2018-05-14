//
//  Wordladder.cpp
//  WordLadder
//
//  Created by James on 11/11/15.
//  Copyright © 2015 James Dalton. All rights reserved.
//

#include "Wordladder.hpp"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <time.h>

using namespace std;

Wordladder::Wordladder() {
    
    // Title
    cout << "== == == == == Word Ladder Solver == == == == ==";
    cout << endl << endl;
    
    
    // Open txt file containing the dictionary of words
    wordsFile.open("/Users/James/Dropbox/Development/WordLadder/WordLadder/words.txt");
    // Check for error in openning word file
    if (wordsFile.fail()) {
        cerr << "ERROR: Unable to open file" << endl;
        exit(1);
    }
}

Wordladder::~Wordladder() {
    
    // Close txt file containing the dictionary of words
    wordsFile.close();
}

void Wordladder::start() {
    
    getWords();             // prompt the user to provide two, four letter words
    checkWords();           // check if words given are found inside the dictionary
    loadWords();            // load word.txt into dictionary
    solver();               // word ladder algorithm
}

void Wordladder::loadWords() {
    
    string tempWord;
    // reduce the number of words added to the list, if possible
    // find the letters that are common
    bool first=false, second=false, third=false, fourth=false;
    short int numLettersInCommon = 0; // var to count how many letter are common between the two words
    short int x=-1, y=-1, z=-1;
    
    for (int i = 0; i < 4; i++) {
        if (word1[i] == word2[i]) {
            if (i == 0) { first=true; numLettersInCommon++; }
            else if (i == 1) { second=true; numLettersInCommon++; }
            else if (i == 2) { third=true; numLettersInCommon++; }
            else { fourth=true; numLettersInCommon++; }
        }
    }
    
    // get back to the beginning of the txt file because we will need to traverse the whole file again
    wordsFile.clear();
    wordsFile.seekg(0, ios::beg);
    switch (numLettersInCommon) {
        case 1:
            // one letter is common
            // test which letter is the common one
            if (first) x=0;
            else if (second) x=1;
            else if (third) x=2;
            else if (fourth) x=3;
            
            while (!wordsFile.eof()) {
                wordsFile >> tempWord;
                // test the conditions
                if (tempWord[x] == word1[x]) {
                    dictionary.push_back(tempWord); // load word into list
                }
            }
            //cout << endl << numLettersInCommon << " letter is in common\n";
            //cout << "Letter " << word1[x]  << " is common\n";
            break;
        case 2:
            // two letter are common
            // test which letters are the common ones
            if (first) {
                x=0;
                if (second) y=1;
                else if (third) y=2;
                else if (fourth) y=3;
            }
            else if (second) {
                x=1;
                if (third) y=2;
                else if (fourth) y=3;
            }
            else if(third) {
                x=2;
                y=3;
            }
            
            while (!wordsFile.eof()) {
                wordsFile >> tempWord;
                // test the conditions
                if (tempWord[x] == word2[x] && tempWord[y] == word2[y]) {
                    dictionary.push_back(tempWord); // load word into list
                }
            }
            //cout << endl << numLettersInCommon << " letters are in common\n";
            //cout << "Letters " << word1[x] << " " << word1[y] << " are common\n";
            break;
        case 3:
            // three letters are common
            // test which letters are the common ones
            if (first) {
                x=0;
                if (second) {
                    y=1;
                    if (third) z=2;
                    else if (fourth) z=4;
                }
                else if (third) {
                    y=2;
                    z=3;
                }
            }
            else if (second) {
                x=1;
                if (third) {
                    y=2;
                    z=3;
                }
            }
            
            while (!wordsFile.eof()) {
                wordsFile >> tempWord;
                // test the conditions
                if (tempWord[x] == word1[x] && tempWord[y] == word1[y] && tempWord[z] == word1[z]) {
                    dictionary.push_back(tempWord); // load word into list
                }
            }
            //cout << endl << numLettersInCommon << " letters are in common\n";
            //cout << "Letters " << word1[x] << " " << word1[y] << " " << word1[z] << " are common\n";
            break;
        case 4:
            // all letter are common -- both words are the same, so throw error
            cerr << "\nERROR: Start word cannot be the same as the target word\n";
            exit(1);
            break;
        default:
            // zero letters are common -- this will be the most common case
            while (!wordsFile.eof()) {
                wordsFile >> tempWord;
                dictionary.push_back(tempWord); // load word into list
            }
            //cout << numLettersInCommon << " letters were in common" << endl;
            break;
    }
    
    // Print list
    /*for( dictionaryIt = dictionary.begin(); dictionaryIt != dictionary.end(); ++dictionaryIt)
        cout << *dictionaryIt << " ";*/
    
    cout << endl;
}

void Wordladder::getWords() {
    
    cout << "Please enter two, four letter words" << endl;
    
    // Get first word
    cout << "Start Word: ";
    cin >> word1;
    // Test words for length. if word is not proper length, run loop until it is
    while (word1.length() != 4) {
        cerr << "\nERROR: Please enter only four letter words\n";
        cout << "Start Word: ";
        cin >> word1;
    }
    cout << "OK" << endl;
    
    
    // Get second word
    cout << "Target Word: ";
    cin >> word2;
    // Test words for length. if word is not proper length, run loop until it is
    while (word2.length() != 4) {
        cerr << "\nERROR: Please enter only four letter words\n";
        cout << "Target Word: ";
        cin >> word2;
    }
    cout << "OK" << endl;
    
    
    // Change both words to uppercase
    for (int i = 0; i < word1.length(); i++) {
        word1[i] = word1[i] & 0xDF;
        word2[i] = word2[i] & 0xDF;
    }
}

int Wordladder::checkWords() {
    
    // Check that words are found inside the dictionary
    string tempWord;
    bool word1Found = false;
    bool word2Found = false;
    
    while (!wordsFile.eof() && (word1Found != true || word2Found != true)) {
        wordsFile >> tempWord;
        if (word1 == tempWord) word1Found = true;
        if (word2 == tempWord) word2Found = true;
    }
    
    if (word1Found == true && word2Found == true) {
        //cout << endl << "Both words were found in the dictionary" << endl;
        return 0;
    }
    else {
        // words were not found in the dictionary
        cerr << "\nERROR: Please provide words found inside a dictionary\n";
        exit(1);
    }
    
}

void Wordladder::solver() {
    
    beginCounter();
    
    /* algorithm to solve word ladder */
    
    Graph g(dictionary);
    cout << "------------------------------" << endl;
    
    // Get shortest path
    list<string> lePath = g.shortestPath(word1, word2);
    
    // Output results of word ladder solver
    cout << "Word ladder: " << endl;
    for (list<string>::iterator it = lePath.begin(); it != lePath.end(); ++it) {
        cout << *it << endl;
    }
    
    stopCounter();
    
    // output the time that was taken to solve word ladder
    cout << endl << "Clock ticks: " << t << endl;
    cout << "Time to solve word ladder (s): " << float(t)/CLOCKS_PER_SEC << " seconds" << endl << endl;
}

clock_t Wordladder::beginCounter() {
    
    // start initial tick counter
    t = clock();
    return t;
}

clock_t Wordladder::stopCounter() {
    
    // refresh clock ticks
    t = clock() - t;

    return t;
}
































