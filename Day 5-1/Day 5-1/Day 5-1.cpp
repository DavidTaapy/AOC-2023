#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>

using namespace std;

int main()
{
    ifstream myFile("Input.txt");
    long long result = INT_MAX;

    if (!myFile.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return -1;
    }

    long long val;
    string line;
    vector<long long> seedsVector;

    for (int i = 0; i < 2; i++) {
        getline(myFile, line);
        if (line != "") {
            size_t colonPos = line.find(':');
            string seedValues = line.substr(colonPos + 1);

            istringstream iss(seedValues);
            while (iss >> val) seedsVector.push_back(val);
        }
    }
    
    vector<vector<vector<long long>>> allMaps;
    vector<vector<long long>> currMap;
    while (getline(myFile, line)) {
        if (line == "") {
            allMaps.push_back(currMap);
            currMap.clear();
        }
        if (line != "" && isdigit(line[0])) {
            vector<long long> currLine;
            istringstream iss(line);
            while (iss >> val) currLine.push_back(val);
            currMap.push_back(currLine);
        }
    }
    allMaps.push_back(currMap);

    for (long long seed : seedsVector) {
        for (vector<vector<long long>> currMap : allMaps) {
            for (vector<long long> line : currMap) {
                if (line[1] <= seed && seed <= (line[1] + line[2] - 1)) {
                    seed += (line[0] - line[1]);
                    break;
                }
            }
        }
        result = seed < result ? seed : result;
    }

    cout << "Result is " << result;
}