#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <algorithm>

using namespace std;

long long getMinValue(vector<pair<long long, long long>> rangePairs);

int main()
{
    ifstream myFile("Input.txt");
    long long result = UINT32_MAX;

    if (!myFile.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return -1;
    }

    long long val;
    string line;
    vector<pair<long long, long long>> seedsVector;

    for (int i = 0; i < 2; i++) {
        getline(myFile, line);
        if (line != "") {
            size_t colonPos = line.find(':');
            string seedValues = line.substr(colonPos + 1);

            istringstream iss(seedValues);
            while (iss >> val) {
                long long val2;
                iss >> val2;
                seedsVector.push_back(make_pair(val, val2));
            }
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

    for (pair<long long, long long> seedRange : seedsVector) {
        vector<pair<long long, long long>> rangePairs = { make_pair(seedRange.first, seedRange.first + seedRange.second - 1) };
        for (vector<vector<long long>> currMap : allMaps) {
            vector<pair<long long, long long>> newRangePairs = {};
            while (!rangePairs.empty()) {
                long long start, end;
                pair<long long, long long> currPair = rangePairs.back();
                rangePairs.pop_back();
                start = currPair.first;
                end = currPair.second;
                bool hasRelevantLine = false;
                for (vector<long long> line : currMap) {
                    if (start >= line[1]) {
                        // Given line covers the range fully
                        if (end <= (line[1] + line[2] - 1)) {
                            start += (line[0] - line[1]);
                            end += (line[0] - line[1]);
                            newRangePairs.push_back(make_pair(start, end));
                            hasRelevantLine = true;
                            break;
                        }
                        // Given line covers the range partially from the start
                        else if (start <= line[1] + line[2] - 1) {
                            long long leftoverStart = line[1] + line[2];
                            long long leftoverEnd = end;
                            rangePairs.push_back(make_pair(leftoverStart, leftoverEnd));
                            start += (line[0] - line[1]);
                            end = leftoverStart - 1 + (line[0] - line[1]);
                            newRangePairs.push_back(make_pair(start, end));
                            hasRelevantLine = true;
                            break;
                        }
                    }
                    else if (end <= line[1] + line[2] - 1) {
                        // Given line covers the range partially until the end
                        if (end >= line[1]) {
                            long long leftoverStart = start;
                            long long leftoverEnd = line[1] - 1;
                            rangePairs.push_back(make_pair(leftoverStart, leftoverEnd));
                            start = line[1] + (line[0] - line[1]);
                            end += (line[0] - line[1]);
                            newRangePairs.push_back(make_pair(start, end));
                            hasRelevantLine = true;
                            break;
                        }
                    }
                    else if (end > line[1] + line[2] - 1) {
                        rangePairs.push_back(make_pair(start, line[1] - 1));
                        rangePairs.push_back(make_pair(line[1] + line[2], end));
                        start = line[0];
                        end = line[0] + line[2] - 1;
                        newRangePairs.push_back(make_pair(start, end));
                        hasRelevantLine = true;
                        break;
                    }
                }
                if (!hasRelevantLine) newRangePairs.push_back(currPair);
            }
            rangePairs = newRangePairs;
        }

        // Get the minimum of the starting ranges of all pairs
        long long currMinVal = getMinValue(rangePairs);
        result = currMinVal < result ? currMinVal : result;
    }

    cout << "Result is " << result;
}

long long getMinValue(vector<pair<long long, long long>> rangePairs) {
    long long minVal = UINT32_MAX;
    for (pair<long long, long long> range : rangePairs) {
        if (range.first < minVal) minVal = range.first;
    }

    return minVal;
}