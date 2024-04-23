#ifndef FINALPROJECT_DSA_STATESGRAPH_H
#define FINALPROJECT_DSA_STATESGRAPH_H

#include <iostream>
#include <fstream>
#include <tuple>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <utility>
#include "DataSets.h"

using namespace std;

class StatesGraph
{
private:

    struct Node
    {
        string name;
        vector<Node*> subNodes; //Head -> States -> (by year) Counties
        vector<Node*> adjacentNodes; //State points to other states, county points to other counties within state.
        string population = "N/A";
        string numDeaths = "N/A";
        string numYear;
        map<string, vector<pair<string, Node*>>> countiesMap;
        int nodeID = 0; //Each node gets a unique ID

    };

    bool exit = false;
    map<string, Node*> statesMap;

    Node* graphHead = nullptr;
    Node* graphCurrent = nullptr;

    int numNodes = 0;

    vector<vector<int>> adjMatrix;

public:

    //Create a graph of all 50 US states with states having connections to one another and counties within each state having connections.
    StatesGraph(vector<tuple<string, string, string, string,string>>& dataStream);

    //Recursively traverse through
    void traverseGraph(int level);

    //Print every county's data for the current US state.
    void printState(Node*);

    //Iterate through the graph and print every county's data by US state.
    void printAll();

    //Connect all 50 states to show that they are the same type of entity.
    void connectStates();

    //Connect counties within each state to show that they are related.
    void connectCounties(map<string, vector<pair<string, Node*>>>& allCounties);

    //Print graph data.
    void findState();
    void findCounty();
    void findYear();

    void emptyMatrix(int nodeCount);  // Construct empty adjacency matrix (all values are 0) of size = numNodes.

    void fillMatrix(Node* head);   //Recursively pass through the graph and update the adjacency matrix

    vector<vector<int>> getMatrix();   //Return the adjacency matrix

    void printMatrix();  //Print the adjacency matrix

    void printEdges();  //Loop over the adjacency matrix and print a list of edges.

    //Graph destructor.
    //~StatesGraph();

};
#endif //FINALPROJECT_DSA_STATESGRAPH_H

