#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <algorithm>

using namespace std;

unsigned long long getNumbersAsLong(string strForm);
unsigned long long findNumberOfWinningSituations(unsigned long long currTime, unsigned long long currDistance);

unsigned long long getNumbersAsLong(string strForm) {
    string resultStr = "";
    for (char character : strForm) {
        if (isdigit(character)) resultStr += character;
    }

    return stoull(resultStr);
}

unsigned long long findNumberOfWinningSituations(unsigned long long maxTime, unsigned long long record) {
    unsigned long long result = 0;
    for (unsigned long long time = 1; time < maxTime; time++) {
        unsigned long long currResult = time * (maxTime - time);
        if (currResult >= record) {
            result++;
        }
        else {
            if (result > 0) {
                break;
            }
        }
    }

    return result;
}

int main()
{
    ifstream myFile("Input.txt");
    unsigned long long result = 0;

    if (!myFile.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return -1;
    }

    string line;
    unsigned long long time;
    unsigned long long distance;
    for (int i = 0; i < 2; i++) {
        getline(myFile, line);
        string numPart = line.substr(line.find(':') + 1);

        if (i == 0) time = getNumbersAsLong(numPart);
        if (i == 1) distance = getNumbersAsLong(numPart);
    }

    result = findNumberOfWinningSituations(time, distance);

    cout << "Result is " << result;
}