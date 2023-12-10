#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_set>
#include <unordered_map>

using namespace std;

vector<long> getNumbersAsVector(string strForm);
vector<long> findCommonElements(vector<long> vector1, vector<long> vector2);

vector<long> getNumbersAsVector(string strForm) {
    string number;
    vector<long> vector;
    istringstream stream(strForm);

    while (stream >> number) vector.push_back(stol(number));

    return vector;
}

vector<long> findCommonElements(vector<long> vector1, vector<long> vector2) {
    unordered_set<long> set1(vector1.begin(), vector1.end());
    vector<long> commonElements;

    for (long num : vector2) {
        if (set1.find(num) != set1.end()) {
            commonElements.push_back(num);
        }
    }

    return commonElements;
}

int main()
{
    ifstream myFile("Input.txt");
    long result = 0;

    if (!myFile.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return -1;
    }

    int numGames = 0;
    string line;
    unordered_map<long, long> scoreDict;
    
    while (getline(myFile, line)) {
        size_t splitPos = line.find('|');
        string firstPart = line.substr(line.find(':') + 1, splitPos - line.find(':') - 1);
        string secondPart = line.substr(splitPos + 1);

        vector<long> firstPartVec = getNumbersAsVector(firstPart);
        vector<long> secondPartVec = getNumbersAsVector(secondPart);
        vector<long> commonElements = findCommonElements(firstPartVec, secondPartVec);

        scoreDict[++numGames] = commonElements.size();
    }

    unordered_map<long, long> finalDict;
    for (int i = 1; i <= scoreDict.size(); i++) finalDict[i] = 1;

    for (auto it = scoreDict.begin(); it != scoreDict.end(); it++) {
        long gameNum = it->first;
        long score = it->second;

        for (int i = 1; i <= score; i++) {
            if (gameNum + i <= numGames) {
                finalDict[gameNum + i] += finalDict[gameNum];
            }
        }

        result += finalDict[gameNum];
    }

    cout << "Result is " << result;
}