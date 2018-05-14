//
//  Graph.hpp
//  WordLadder
//
//  Created by James on 11/26/15.
//  Copyright © 2015 James Dalton. All rights reserved.
//

#ifndef Graph_hpp
#define Graph_hpp

#include <stdio.h>
#include <iostream>
#include <list>
#include <vector>

using namespace std;

struct Node
{
    string data;
    string parent;
};

// This class represents a directed graph using adjacency list representation
class Graph
{
private:
    unsigned long V;    // No. of vertices
    vector<string> values; // change to str and load it with dictionary
    list<Node> path; // the list of paths from start to destination
    vector<string> dictionary; // dictionary of words
    
    list<Node> BFS(string start ,string destination);  // prints BFS traversal from a given source s
    int getLocation(string value); // search the vector
    string getValue(int location); // directly access the vector
    
public:
    Graph(vector<string> dict);  // Constructor
    list<string> shortestPath(string s, string d); // Will return the shortest path from start to destination
};

#endif /* Graph_hpp */
