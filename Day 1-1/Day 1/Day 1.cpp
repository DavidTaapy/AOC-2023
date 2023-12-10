#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int getFirstDigitFromFront(string line) {
    for (int i = 0; i < line.size(); i++) {
        if (isdigit(line[i])) return line[i] - '0';
    }
}

int getFirstDigitFromBack(string line) {
    for (int i = line.size() - 1; i >= 0; i--) {
        if (isdigit(line[i])) return line[i] - '0';
    }
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
        result += getFirstDigitFromFront(line) * 10 + getFirstDigitFromBack(line);
    }

    cout << "Final result is " << result;
}