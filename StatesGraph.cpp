#include "StatesGraph.h"
#include <iostream>
#include <vector>
#include <map>
#include <tuple>
#include <chrono>

StatesGraph::StatesGraph(vector<tuple<string, string, string, string, string>>& dataStream) {
    Node* head = new Node; // Head node
    graphHead = head;
    head->name = "graph head";

    head->nodeID = numNodes; //Give each new node its unique ID
    numNodes++;

    for (const auto& entry : dataStream) {
        string currentCounty = get<0>(entry);
        string currentState = get<1>(entry);
        string currentDeaths = get<2>(entry);
        string currentPop = get<3>(entry);
        string currentYear = get<4>(entry);

        // N/A if data does not exist for this field.
        if(currentDeaths.empty())
        {
            currentDeaths = "N/A";
        }
        if(currentPop.empty())
        {
            currentPop = "N/A";
        }

        // Check if the state exists, and add if not
        if (statesMap.find(currentState) == statesMap.end()) {
            Node* newState = new Node;
            newState->name = currentState;


            head->subNodes.push_back(newState);
            statesMap[currentState] = newState;

            newState->nodeID = numNodes;
            numNodes++;
        }

        // Access state node
        Node* stateNode = statesMap[currentState];

        // Check for existing county and year
        bool found = false;
        for (auto& pair : stateNode->countiesMap[currentCounty]) {
            if (pair.first == currentYear) { // Year exists
                found = true;
                break;
            }
        }

        // If not found, add new county with year
        if (!found) {
            Node* newCounty = new Node;
            newCounty->name = currentCounty;
            newCounty->population = currentPop;
            newCounty->numDeaths = currentDeaths;
            newCounty->numYear = currentYear;

            stateNode->subNodes.push_back(newCounty);
            stateNode->countiesMap[currentCounty].emplace_back(currentYear, newCounty);

            newCounty->nodeID = numNodes;
            numNodes++;
        }
    }

    connectStates();

    ///   Call adjacency matrix
    emptyMatrix(numNodes);
    fillMatrix(graphHead);
}

//Print each county in the specified state in alphabetical order.
void StatesGraph::printState(Node* state)
{
    map<string, vector<pair<string, Node*>>>::iterator iter;

    for(iter = state->countiesMap.begin(); iter != state->countiesMap.end(); iter++)
    {
        cout << iter->first << endl;
        const auto& counties = iter->second;

        for (const auto& county : counties) {
            const std::string& year = county.first;  // Year as string
            const Node* node = county.second;  // Pointer to the Node structure

            std::cout << "\tYear: " << year << std::endl;
            std::cout << "\tPopulation: " << node->population << std::endl;
            std::cout << "\tDeaths: " << node->numDeaths << std::endl;
            std::cout << "\t---------------------------------" << std::endl;
        }
    }
}

//Prints every state on the graph in alphabetical order.
void StatesGraph::printAll()
{
    map<string, Node*>::iterator iter;
    for(iter = statesMap.begin(); iter != statesMap.end(); iter++)
    {
        cout << "State:" << iter->second->name << endl;
        printState(iter->second); //Print each county in the state in alphabetical order.
    }
}

//Connect all 50 states to show that they are the same type of entity.
void StatesGraph::connectStates()
{
    map<string, Node*>::iterator iter1;
    map<string, Node*>::iterator iter2;

    //Each state is connected to each other state.
    for(iter1 = statesMap.begin(); iter1 != statesMap.end(); iter1++)
    {
        for(iter2 = iter1; iter2 != statesMap.end(); iter2++)
        {
            if(iter1->second->nodeID != iter2->second->nodeID)
            {
                iter1->second->adjacentNodes.push_back(iter2->second);
                iter2->second->adjacentNodes.push_back(iter1->second);
            }
        }

        connectCounties(iter1->second->countiesMap);
    }
}

//Connect counties within each state to show that they are related. Nodes are only connected if they are from the same year.
void StatesGraph::connectCounties(map<string, vector<pair<string, Node*>>>& allCounties)
{
map<string, vector<pair<string, Node*>>>::iterator iter1;
map<string, vector<pair<string, Node*>>>::iterator iter2;

vector<string> years{"2008", "2009", "2010", "2011", "2012", "2013"};
string year = years[0];

Node* currentNode = nullptr;

for(int i = 0; i < 6; i++)
{
year = years[i];
bool found = false;

//Each county Node is connected to each other county Node within the same year.
for(iter1 = allCounties.begin(); iter1 != allCounties.end(); iter1++)
{
//Find this county's node for the current year
for (auto& pair : iter1->second)
{
if (pair.first == year)  // Year exists
{
currentNode = pair.second;
found = true;
break;
}
}

if(found)
{
for(iter2 = iter1; iter2 != allCounties.end(); iter2++)
{
for (auto& pair : iter2->second)
{
if (pair.first == year && iter1 != iter2)  // Year exists
{
// Nodes only connect to nodes that share the same year.
currentNode->adjacentNodes.push_back(pair.second);
pair.second->adjacentNodes.push_back(currentNode);
break;
}
}
}
}
}
}
}

void StatesGraph::findState(){
    auto start = std::chrono::high_resolution_clock::now();
    string state;
    cout << "Choose a State" << endl;
    getline(cin,state);
    auto it = statesMap.find(state);
    if (it != statesMap.end()) {
        printState(it->second);
    } else {
        std::cout << "State not found." << '\n';
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "Time taken by function: " << duration.count() << " milliseconds" << std::endl;
}

void StatesGraph::findCounty() {
    string state;
    cout << "Choose a State" << endl;
    getline(cin,state);

    string county;
    cout << "Choose a County" << endl;
    getline(cin,county);

    string year;
    cout << "Choose a Year: 2008, 2009, 2010, 2011, 2012, 2013. (Write \"All\" to print all years)"<< endl;
    getline(cin,year);
    auto start = std::chrono::high_resolution_clock::now();
    auto stateIter = statesMap.find(state);
    if (stateIter != statesMap.end()) {

        Node* stateNode = stateIter->second;
        auto countyIter = stateNode->countiesMap.find(county);
        if (countyIter != stateNode->countiesMap.end()) {
            cout << county << " in state: " << state << endl;
            for (const auto& yearPair : countyIter->second) {
                if(yearPair.first == year){
                    cout << "Population: " << yearPair.second->population <<endl;
                    cout << "Deaths: " << yearPair.second->numDeaths << endl;
                    cout << "-----------------------------" << endl;
                }
                else if(year == "All"){
                    cout << "Population: " << yearPair.second->population <<endl;
                    cout << "Deaths: " << yearPair.second->numDeaths << endl;
                    cout << "Year: " << yearPair.first <<endl;
                    cout << "-----------------------------" << endl;
                }
            }
        } else {
            cout << "County " << county << " not found in state " << county << endl;
        }
    } else {
        cout << "State " << state << " not found." << endl;
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto durationNano = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
    std::cout << "Time taken by function: " << durationNano.count() << " nanoseconds" << std::endl;

}

void StatesGraph::findYear() {
    string year;
    cout << "Choose a Year: 2008, 2009, 2010, 2011, 2012, 2013. (Write \"All\" to print all years)"<< endl;
    getline(cin,year);
    map<string, Node*>::iterator iter;


    string stateName;
    cout << "Choose a State: (Write \"All\" to print all the states)" << endl;
    getline(cin,stateName);

    auto start = std::chrono::high_resolution_clock::now();
    if(stateName == "All") {
        for (auto &State: statesMap) {
            cout << "State:" << State.second->name << endl;
            for (auto &countyPair: State.second->countiesMap) {
                cout << "County: " << countyPair.first << endl;

                for (const auto &yearData: countyPair.second) {
                    const string &dataYear = yearData.first;
                    const Node *node = yearData.second;

                    // Check if the user input matches the data year or if the user wants all years
                    if (year == dataYear || year == "All") {
                        cout << "\tYear: " << dataYear << endl;
                        cout << "\tPopulation: " << node->population << endl;
                        cout << "\tDeaths: " << node->numDeaths << endl;
                        cout << "\t---------------------------------" << endl;
                    }
                }
            }
        }
    }
    else {
        auto stateIter = statesMap.find(stateName);
        if (stateIter != statesMap.end()) {
            cout << "State:" << stateIter->second->name << endl;
            for (auto &countyPair: stateIter->second->countiesMap) {
                cout << "County: " << countyPair.first << endl;

                for (const auto &yearData: countyPair.second) {
                    const string &dataYear = yearData.first;
                    const Node *node = yearData.second;

                    // Check if the user input matches the data year or if the user wants all years
                    if (year == dataYear || year == "All") {
                        cout << "\tYear: " << dataYear << endl;
                        cout << "\tPopulation: " << node->population << endl;
                        cout << "\tDeaths: " << node->numDeaths << endl;
                        cout << "\t---------------------------------" << endl;
                    }
                }
            }
        } else{
            cout << "Not found "<< endl;
        }
        auto stop = std::chrono::high_resolution_clock::now();
        auto durationNano = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
        std::cout << "Time taken by function: " << durationNano.count() << " nanoseconds" << std::endl;
    }
}

void StatesGraph::emptyMatrix(int nodeCount)
{
    for(int i = 0; i < nodeCount; i++)
    {
        vector<int> weights;
        for(int j = 0; j < nodeCount; j++)
        {
            weights.push_back(0);
        }
        adjMatrix.push_back(weights);
    }
}

//Recursively pass through the graph and update the adjacency matrix
void StatesGraph::fillMatrix(Node* head)
{
    for(int i = 0; i < head->subNodes.size(); i++)
    {
        //cout << head->name;
        adjMatrix[head->nodeID][head->subNodes[i]->nodeID] = 1; // Graph[from][to] = 1 if there is a path and 0 otherwise.
        fillMatrix(head->subNodes[i]); //Recursively visit each other node.
    }
    for(int j = 0; j < head->adjacentNodes.size(); j++)
    {
        adjMatrix[head->nodeID][head->adjacentNodes[j]->nodeID] = 1;
    }
}

//Return the adjacency matrix.
vector<vector<int>> StatesGraph::getMatrix()
{
    return adjMatrix;
}

//Print the adjacency matrix
void StatesGraph::printMatrix()
{
    for(int i = 0; i < adjMatrix.size(); i++)
    {
        for(int j = 0; j < adjMatrix.size(); j++)
        {
            cout << adjMatrix[i][j];   // Print each value of the adjacency matrix with same [to] rows on the same line.

            if(j != adjMatrix.size() - 1)
            {
                cout << ", "; //Separator other than a space since the entire row won't be on the same line of the terminal when printed.
            }
        }
        cout << endl;
        cout << endl;  //Separator used to make clear where a new line happens.
    }
    cout << "-----------------------------" << endl;
}

void StatesGraph::printEdges()
{
    cout << "From: \t To:" << endl;
    for (int i = 0; i < adjMatrix.size(); i++)
    {
        for (int j = 0; j < adjMatrix.size(); j++)
        {
            if (adjMatrix[i][j] != 0)
            {
                cout << i << "\t" << j << endl; //Only print indices if an edge exists.
            }
        }
    }
    cout << "-----------------------------" << endl;
}