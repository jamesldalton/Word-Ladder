//
//  main.cpp
//  WordLadder
//
//  Created by James on 11/10/15.
//  Copyright © 2015 James Dalton. All rights reserved.
//

#include <iostream>
#include "Wordladder.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    
    // program info
    cout << "Name: James Dalton - Program: Word Ladder Solver - Date: Dec 6, 2015\n";
    
    // declare instance of Wordladder solver
    Wordladder solver;
    
    // begin solver
    solver.start();
    
    return 0;
}
