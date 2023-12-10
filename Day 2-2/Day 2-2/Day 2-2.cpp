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

long returnSumOfCubes(string line) {
    vector<string> colours = { "red", "green", "blue" };
    long sumOfCubes = 1;

    for (int i = 0; i < colours.size(); i++) {
        string currColour = colours[i];
        vector<long> currValues = extractNumbers(currColour, line);
        sumOfCubes *= *max_element(begin(currValues), end(currValues));
    }

    return sumOfCubes;
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
    while (getline(myFile, line)) {
        result += returnSumOfCubes(line);
    }

    cout << "Result is " << result;
}