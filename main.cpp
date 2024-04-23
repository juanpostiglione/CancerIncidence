#include "DataSets.h"
#include "StatesGraph.h"

using namespace std;

int main() {

    DataSets datasets;
    /// Constants for the base directory and file extension.
    string baseDirectory = "data/"; /// Data path directory.
    vector<string> filenames = { "dataSet2008.csv" , "dataSet2009.csv", "dataSet2010.csv", "dataSet2011.csv", "dataSet2012.csv", "dataSet2013.csv" };
    vector<string> years = { "2008", "2009", "2010", "2011", "2012", "2013" };
    vector<DataSets::TupleCancerData> allData;

    int i = 0;

    for (auto files : filenames)
    {
        /// Get the full file path using the base directory and file extension
        string filename = baseDirectory + files;

        /// Read and process the data from the specified file
        vector<DataSets::TupleCancerData> data = datasets.readData(filename, years[i]);
        allData.insert(allData.end(), data.begin(), data.end());

        i++;
    }

    /// Create the graph and get necessary values
    StatesGraph graph(allData);

    while (true) {
        string type;
        cout << "How do you want to read the data? Graph or Directly" << endl;
        cout << "Enter \"Exit\" to quit" << endl;
        getline(cin, type);

        if (type == "Graph") {
            string input;
            cout << "1) Search by State (Enter 1)" << endl;
            cout << "2) Search by County (Enter 2)" << endl;
            cout << "3) Search by Year (Enter 3)" << endl;
            cout << "4) Display Adjacency Matrix (Enter 4)" << endl;
            cout << "5) Display Edge List (Enter 5)" << endl;
            getline(cin, input);
            if (input == "1") {
                graph.findState();
            }
            else if (input == "2") {
                graph.findCounty();
            }
            else if (input == "3") {
                graph.findYear();
            }
            else if (input == "4") {
                graph.printMatrix();
            }
            else if (input == "5") {
                graph.printEdges();
            }
            else {
                cout << "Invalid Option. Try Again" << endl;
            }
        }
        else if (type == "Directly") {
            datasets.printData(allData);
        }
        else if (type == "Exit")
        {
            break;
        }
    }

    return 0;
}