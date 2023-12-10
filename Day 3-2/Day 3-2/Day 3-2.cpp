#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <set>

using namespace std;

struct Cell {
    long row_idx;
    long col_idx;
    string strVal;

    Cell(long row_idx, long col_idx, string strVal) : row_idx(row_idx), col_idx(col_idx), strVal(strVal) {}
};

bool neighboursHaveSymbol(vector<vector<Cell>> inputMap, Cell currCell, long lenNum);
void updateValueIfHasAdjacentSymbol(vector<vector<Cell>>& inputMap, Cell currCell);
bool withinBounds(long currRow, long currCol, long maxRows, long maxCols);
pair<string, long> getWholeNumber(vector<Cell>& currRowCells, long currCol);
void updateNumberValues(vector<vector<Cell>>& inputMap, Cell currCell, long lenNum, string strVal);
void processInputMap(vector<vector<Cell>>& inputMap);
set<long> returnAdjacentPartNumbersIfGear(vector<vector<Cell>>& inputMap, long rowIdx, long colIdx);
vector<vector<long>> generateNeighbours(long rowIdx, long colIdx);

vector<vector<long>> generateNeighbours(long rowIdx, long colIdx) {
    vector<vector<long>> neighbourCellsIdx = {
        {rowIdx - 1, colIdx - 1}, {rowIdx - 1, colIdx}, {rowIdx - 1, colIdx + 1},
        {rowIdx, colIdx - 1}, {rowIdx, colIdx + 1},
        {rowIdx + 1, colIdx - 1}, {rowIdx + 1, colIdx}, {rowIdx + 1, colIdx + 1}
    };

    return neighbourCellsIdx;
}

bool neighboursHaveSymbol(vector<vector<Cell>> inputMap, Cell currCell, long lenNum) {
    for (int i = 0; i < lenNum; i++) {
        for (vector<long> neighbourIdx : generateNeighbours(currCell.row_idx, currCell.col_idx + i)) {
            long currRow = neighbourIdx.at(0);
            long currCol = neighbourIdx.at(1);

            if (withinBounds(currRow, currCol, inputMap.size(), inputMap.at(0).size())) {
                string currStr = inputMap.at(currRow).at(currCol).strVal;
                if (currStr.size() == 1 && !isdigit(currStr[0]) && currStr != ".") {
                    return true;
                }
            }
        }
    }

    return false;
}

void updateValueIfHasAdjacentSymbol(vector<vector<Cell>>& inputMap, Cell currCell) {
    string currStr = currCell.strVal;

    if ((currStr.size() == 1 && isdigit(currStr[0]))) {
        vector<Cell>& currRowCells = inputMap.at(currCell.row_idx);
        string strVal = currCell.strVal;
        long lenNum;
        tie(strVal, lenNum) = getWholeNumber(currRowCells, currCell.col_idx);

        if (neighboursHaveSymbol(inputMap, currCell, lenNum)) {
            updateNumberValues(inputMap, currCell, lenNum, strVal);
        }
        else {
            inputMap.at(currCell.row_idx).at(currCell.col_idx).strVal = ".";
        }
    }
}

bool withinBounds(long currRow, long currCol, long maxRows, long maxCols) {
    return (0 <= currRow && currRow < maxRows && 0 <= currCol && currCol < maxCols);
}

pair<string, long> getWholeNumber(vector<Cell>& currRowCells, long currCol) {
    string result = "";
    long lenOfNumber = 0;
    while (currCol < currRowCells.size()) {
        char currChar = currRowCells.at(currCol).strVal[0];       
        if (!isdigit(currChar)) return make_pair(result, lenOfNumber);

        result.push_back(currChar);
        currCol++;
        lenOfNumber++;
    }
    return make_pair(result, lenOfNumber);
}

void updateNumberValues(vector<vector<Cell>>& inputMap, Cell currCell, long lenNum, string strVal) {
    for (int i = 0; i < lenNum; i++) {
        inputMap.at(currCell.row_idx).at(currCell.col_idx + i).strVal = strVal;
    }
}

void processInputMap(vector<vector<Cell>>& inputMap) {
    long maxRow = inputMap.size();
    long maxCol = inputMap.at(0).size();
;    for (int i = 0; i < maxRow; i++) {
        for (int j = 0; j < maxCol; j++) {
            updateValueIfHasAdjacentSymbol(inputMap, inputMap.at(i).at(j));
        }
    }
}

bool isStringLong(string str) {
    try {
        size_t pos;
        std::stol(str, &pos);
        return pos == str.length();
    }
    catch (exception Ex) {
        return false;
    }
}

set<long> returnAdjacentPartNumbersIfGear(vector<vector<Cell>>& inputMap, long rowIdx, long colIdx) {
    set<long> result;
    if (inputMap.at(rowIdx).at(colIdx).strVal == "*") {
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                string currStr = inputMap.at(rowIdx + i).at(colIdx +j).strVal;
                if (isStringLong(currStr)) {
                    result.insert(stol(currStr));
                }
            }
        }
    }

    return result;
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
    vector<vector<Cell>> inputMap;

    long currRow = 0;
    int currCol;
    while (getline(myFile, line)) {
        vector<Cell> currVector = vector<Cell>();
        for (currCol = 0; currCol < line.size(); currCol++) {
            string currChar(1, line[currCol]);
            currVector.push_back(Cell(currRow, currCol, currChar));
        }
        inputMap.push_back(currVector);
        currRow++;
    }

    processInputMap(inputMap);

    for (int i = 0; i < currRow; i++) {
        for (int j = 0; j < currCol; j++) {
            set<long> adjacentPartNums = returnAdjacentPartNumbersIfGear(inputMap, i, j);
            if (adjacentPartNums.size() == 2) {
                long currProduct = 1;
                for (long partNum : adjacentPartNums) {
                    currProduct *= partNum;
                }
                result += currProduct;
            }
        }
    }

    cout << "Result is " << result;
}