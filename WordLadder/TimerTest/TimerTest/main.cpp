//
//  main.cpp
//  TimerTest
//
//  Created by James on 11/11/15.
//  Copyright © 2015 James Dalton. All rights reserved.
//

#include <iostream>
#include "time.h"
#include <fstream>

using namespace std;



int main(int argc, const char * argv[]) {
    
    string word1, word2;
    
    cout << "Please enter two, four letter words" << endl;
    
    // get first word
    cout << "Word 1: ";
    cin >> word1;
    // test words for length. if word is not proper length, run loop until it is
    while (word1.length() != 4) {
        cerr << "\nERROR: Please enter only four letter words\n";
        cout << "Word 1: ";
        cin >> word1;
    }
    cout << "OK" << endl;
    
    
    // get second word
    cout << endl << "Word 2: ";
    cin >> word2;
    // test words for length. if word is not proper length, run loop until it is
    while (word2.length() != 4) {
        cerr << "\nERROR: Please enter only four letter words\n";
        cout << "Word 2: ";
        cin >> word2;
    }
    cout << "OK" << endl;
    
    
    // change both words to uppercase
    for (int i = 0; i < word1.length(); i++) {
        word1[i] = word1[i] & 0xDF;
        word2[i] = word2[i] & 0xDF;
    }
    
    cout << word1 << endl << word2 << endl;
    
    
    ifstream inFile;
    inFile.open("/Users/James/Dropbox/Development/WordLadder/WordLadder/words.txt");
    
    // check for error
    if (inFile.fail()) {
        cerr << "ERROR: Unable to open file" << endl;
        exit(1);
    }
    
    string word;
    bool word1Found = false;
    bool word2Found = false;
    
    while (!inFile.eof() && (word1Found != true || word2Found != true)) {
        inFile >> word;
        if (word1 == word) word1Found = true;
        if (word2 == word) word2Found = true;
    }
    inFile.close();
    
    if (word1Found == true && word2Found == true) {
        cout << endl << "Both words were found in the dictionary" << endl;
    }
    
    return 0;
}
