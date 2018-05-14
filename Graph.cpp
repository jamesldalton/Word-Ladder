//
//  Graph.cpp
//  WordLadder
//
//  Created by James on 11/26/15.
//  Copyright © 2015 James Dalton. All rights reserved.
//

#include "Graph.hpp"


Graph::Graph(vector<string> dict)
{
    // load dictionary with words
    dictionary = dict;
    this->V = dictionary.size();
}

int Graph::getLocation(string value)
{
    for (int i = 0; i < dictionary.size(); i++) {
        if (dictionary[i] == value)
            return i;
    }
    
    cerr << "\nERROR: Given value cannot be located inside vector\n\n";
    exit(1);
}

string Graph::getValue(int location)
{
    if (location <= dictionary.size()) {
        return dictionary[location];
    } else {
        cerr << "\nERROR: No value can be found at given location\n\n";
        exit(1);
    }
}

list<string> Graph::shortestPath(string s, string d)
{
    // This method will perform a breadth-first search from s to d
    // Once that operation has been performed, this method will
    // take the returned paths list and work back from the des-
    // stination word until the start word has been also found
    // in the list
    
    BFS(s, d);
    
    list<Node>::iterator it;
    list<string> myPath;
    
    for (it = path.begin(); it->data != d; ++it) {} // first, locate destination word inside the paths list
    string num = it->data;
    myPath.push_front(num); // push destination word into another list
    
    while (it != path.begin()) { // if the next node does not have the same value in data as in parent, then continue to search
        num = it->parent;
        myPath.push_front(num);
        for (it=it; it->data != num; --it) {} // continue on to find the location of the parent and so on
    }
    return myPath;
}

list<Node> Graph::BFS(string s, string d)
{
    // Get actual locations of start and destination values
    int start = getLocation(s);
    int destination = getLocation(d);
    
    // Mark all the vertices as not visited
    bool *visited = new bool[V];
    for(int i = 0; i < V; i++)
        visited[i] = false;
    
    // Create a queue for BFS
    list<int> queue;
    
    // Mark the current node as visited and enqueue it
    visited[start] = true;
    queue.push_back(start);
    
    list<int> wordsVaryByOneLetter;
    
    Node n;
    n.data = s;
    n.parent = s;
    path.push_back(n);
    
    while(start != destination && !queue.empty()) // original: !queue.empty()
    {
        // Dequeue a vertex from queue and print it
        start = queue.front();

        queue.pop_front();
        n.parent = getValue(start);
        
        // Find all words inside the dictionary that vary by one letter
        wordsVaryByOneLetter.clear();
        for (int i = 0; i < dictionary.size(); i++)
        {
            if (dictionary[i][0] != dictionary[start][0] && dictionary[i][1] == dictionary[start][1] && dictionary[i][2] == dictionary[start][2] && dictionary[i][3] == dictionary[start][3])
            {
                wordsVaryByOneLetter.push_back(i);
            } else if (dictionary[i][0] == dictionary[start][0] && dictionary[i][1] != dictionary[start][1] && dictionary[i][2] == dictionary[start][2] && dictionary[i][3] == dictionary[start][3])
            {
                wordsVaryByOneLetter.push_back(i);
            } else if (dictionary[i][0] == dictionary[start][0] && dictionary[i][1] == dictionary[start][1] && dictionary[i][2] != dictionary[start][2] && dictionary[i][3] == dictionary[start][3])
            {
                wordsVaryByOneLetter.push_back(i);
            }
            else if (dictionary[i][0] == dictionary[start][0] && dictionary[i][1] == dictionary[start][1] && dictionary[i][2] == dictionary[start][2] && dictionary[i][3] != dictionary[start][3])
            {
                wordsVaryByOneLetter.push_back(i);
            }
        }
        
        // Only put words that have not been visited into queue
        // 'it' will be used to traverse
        list<int>::iterator it;
        for (it = wordsVaryByOneLetter.begin(); it != wordsVaryByOneLetter.end(); ++it)
        {
            if(!visited[*it] /*AND only one letter is different*/)
            {
                visited[*it] = true;
                queue.push_back(*it);
                // Put word into path list
                n.data = dictionary[*it];
                path.push_back(n);
            }
        }
    }

    delete visited;
    return path;
}