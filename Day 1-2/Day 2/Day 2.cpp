#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <regex>

using namespace std;

tuple<int, int> getFirstDigitFromFront(string line) {
    for (int i = 0; i < line.size(); i++) {
        if (isdigit(line[i])) return make_tuple(i, line[i] - '0');
    }
}

tuple<int, int> getFirstDigitFromBack(string line) {
    for (int i = line.size() - 1; i >= 0; i--) {
        if (isdigit(line[i])) return make_tuple(i, line[i] - '0');
    }
}

map<string, char> stringDigitMap = {
        {"one", '1'}, {"two", '2'}, {"three", '3'}, {"four", '4'},
        {"five", '5'}, {"six", '6'}, {"seven", '7'}, {"eight", '8'}, {"nine", '9'}
};

void searchAndUpdate(string line, int& iFirst, int& firstNum, int& iLast, int& lastNum, string toMatch, char toReplaceWith) {
    regex pattern(toMatch);
    smatch match;
    int value = toReplaceWith - '0';
    while (regex_search(line, match, pattern)) {
        if (match.position() < iFirst) {
            iFirst = static_cast<int>(match.position());
            firstNum = value;
        }
        if (match.position() > iLast) {
            iLast = static_cast<int>(match.position());
            lastNum = value;
        }
        line[match.position()] = toReplaceWith;
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
        int iLast, lastNum, iFirst, firstNum;
        tie(iFirst, firstNum) = getFirstDigitFromFront(line);
        tie(iLast, lastNum) = getFirstDigitFromBack(line);

        for (auto i = stringDigitMap.begin(); i != stringDigitMap.end(); i++) {
            searchAndUpdate(line, iFirst, firstNum, iLast, lastNum, i->first, i->second);
        }       
        
        result += firstNum * 10 + lastNum;
    }

    std::cout << "Final result is " << result;
}