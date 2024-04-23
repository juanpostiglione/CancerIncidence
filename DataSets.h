#include <iostream>
#include <fstream>
#include <tuple>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#pragma once

using namespace std;

/// Data Sets Class
class DataSets{
public:

    /// Tuple for Cancer Data
    using TupleCancerData = tuple<string, string, string, string, string>;

    /// Function to read the files
    vector<TupleCancerData> readData(string& filename, string& fileYear);

    /// Function to Print Data
    void printData(vector<TupleCancerData>& data);
};


