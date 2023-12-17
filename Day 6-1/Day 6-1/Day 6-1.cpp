#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <algorithm>

using namespace std;

vector<long> getNumbersAsVector(string strForm);
long findNumberOfWinningSituations(long currTime, long currDistance);

vector<long> getNumbersAsVector(string strForm) {
    string number;
    vector<long> vector;
    istringstream stream(strForm);

    while (stream >> number) vector.push_back(stol(number));

    return vector;
}

long findNumberOfWinningSituations(long maxTime, long record) {
    long result = 0;
    for (long time = 1; time < maxTime; time++) {
        long currResult = time * (maxTime - time);
        if (currResult >= record) result++;
    }

    return result;
}

int main()
{
    ifstream myFile("Input.txt");
    long long result = 0;

    if (!myFile.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return -1;
    }

    string line;
    vector<long> timeVec;
    vector<long> distanceVec;
    for (int i = 0; i < 2; i++) {
        getline(myFile, line);
        string numPart = line.substr(line.find(':') + 1);

        if (i == 0) timeVec = getNumbersAsVector(numPart);
        if (i == 1) distanceVec = getNumbersAsVector(numPart);
    }

    for (int i = 0; i < timeVec.size(); i++) {
        long currTime = timeVec[i];
        long currDistance = distanceVec[i];
        
        long numWinningSituations = findNumberOfWinningSituations(currTime, currDistance);
        if (result == 0 && numWinningSituations > 0) result = 1;
        result *= numWinningSituations;
    }

    cout << "Result is " << result;
}