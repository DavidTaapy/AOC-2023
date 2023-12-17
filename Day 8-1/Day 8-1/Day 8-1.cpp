#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

int main()
{
    ifstream myFile("Input.txt");
    long long result = 0;

    if (!myFile.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return -1;
    }

    string line;
    getline(myFile, line);
    string sequence = line;
    getline(myFile, line);

    unordered_map<string, pair<string, string>> givenMap;
    while (getline(myFile, line)) {
        givenMap[line.substr(0, 3)] = make_pair(line.substr(7, 3), line.substr(12, 3));
    }

    string currPos = "AAA";
    while (currPos != "ZZZ") {
        if (sequence[result % sequence.size()] == 'L') currPos = givenMap[currPos].first;
        else currPos = givenMap[currPos].second;
        result++;
    }

    cout << "Result is " << result;
}