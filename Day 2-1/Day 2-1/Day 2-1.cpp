#include <iostream>
#include <fstream>
#include <string>
#include <regex>

using namespace std;

vector<long> extractNumbers(string color, string input_str) {
    vector<long> numbers;
    regex pattern(" (\\d+) " + color);
    smatch matches;

    auto it = std::sregex_iterator(input_str.begin(), input_str.end(), pattern);
    auto end = std::sregex_iterator();

    for (; it != end; it++) {
        numbers.push_back(std::stol(it->str(1)));
    }

    return numbers;
};

long returnGameIdIfPossible(string line, long currGame) {
    vector<string> colours = { "red", "green", "blue" };
    vector<long> maximum = { 12, 13, 14 };

    for (int i = 0; i < colours.size(); i++) {
        string currColour = colours[i];
        long currMax = maximum[i];
        vector<long> currValues = extractNumbers(currColour, line);
        for (long currVal : currValues) {
            if (currVal > currMax) {
                return 0;
            }
        }
    }

    return currGame;
}

int main()
{
    ifstream myFile("Input.txt");
    long result = 0;

    if (!myFile.is_open()) {
        std::cerr << "Error openinng file!" << std::endl;
        return -1;
    }

    string line;
    long currGame = 1;
    while (getline(myFile, line)) {
        result += returnGameIdIfPossible(line, currGame);
        currGame++;
    }

    cout << "Result is " << result;
}