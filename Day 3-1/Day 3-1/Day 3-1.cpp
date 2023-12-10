#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Cell {
    long row_idx;
    long col_idx;
    char character;

    Cell(long row_idx, long col_idx, char character) : row_idx(row_idx), col_idx(col_idx), character(character) {}
};

bool neighboursHaveSymbol(vector<vector<Cell>> inputMap, Cell currCell);
long returnValueIfHasAdjacentSymbol(vector<vector<Cell>>& inputMap, Cell currCell);
bool withinBounds(long currRow, long currCol, long maxRows, long maxCols);
string checkLeftForDigitAndUpdateValue(vector<Cell>& currRowCells, long currCol);
string checkRightForDigitAndUpdateValue(vector<Cell>& currRowCells, long currCol);
long getNumberValue(vector<vector<Cell>>& inputMap, Cell currCell);

bool neighboursHaveSymbol(vector<vector<Cell>> inputMap, Cell currCell) {
    vector<vector<long>> neighbourCellsIdx = {
        {currCell.row_idx - 1, currCell.col_idx - 1}, {currCell.row_idx - 1, currCell.col_idx}, {currCell.row_idx - 1, currCell.col_idx + 1},
        {currCell.row_idx, currCell.col_idx - 1}, {currCell.row_idx, currCell.col_idx + 1},
        {currCell.row_idx + 1, currCell.col_idx - 1}, {currCell.row_idx + 1, currCell.col_idx}, {currCell.row_idx + 1, currCell.col_idx + 1}
    };

    for (vector<long> neighbourIdx : neighbourCellsIdx) {
        long currRow = neighbourIdx.at(0);
        long currCol = neighbourIdx.at(1);

        if (withinBounds(currRow, currCol, inputMap.size(), inputMap.at(0).size())) {
            char currChar = inputMap.at(currRow).at(currCol).character;
            if (!isdigit(currChar) && currChar != '.') {
                return true;
            }
        }
    }

    return false;
}

long returnValueIfHasAdjacentSymbol(vector<vector<Cell>>& inputMap, Cell currCell) {
    char currChar = currCell.character;

    return (isdigit(currChar) && neighboursHaveSymbol(inputMap, currCell)) ? getNumberValue(inputMap, currCell) : 0;
}

bool withinBounds(long currRow, long currCol, long maxRows, long maxCols) {
    return (0 <= currRow && currRow < maxRows && 0 <= currCol && currCol < maxCols);
}

string checkLeftForDigitAndUpdateValue(vector<Cell>& currRowCells, long currCol) {
    string result = "";
    while (currCol >= 0) {
        char currChar = currRowCells.at(currCol).character;
        if (!isdigit(currChar)) return result;

        currRowCells.at(currCol).character = '.';
        result.insert(result.begin(), currChar);
        currCol--;
    }
    return result;
}

string checkRightForDigitAndUpdateValue(vector<Cell>& currRowCells, long currCol) {
    string result = "";
    while (currCol < currRowCells.size()) {
        char currChar = currRowCells.at(currCol).character;       
        if (!isdigit(currChar)) return result;

        currRowCells.at(currCol).character = '.';
        result.push_back(currChar);
        currCol++;
    }
    return result;
}

long getNumberValue(vector<vector<Cell>>& inputMap, Cell currCell) {
    vector<Cell>& currRowCells = inputMap.at(currCell.row_idx);

    string result = checkLeftForDigitAndUpdateValue(currRowCells, currCell.col_idx - 1);
    result += currCell.character;
    result += checkRightForDigitAndUpdateValue(currRowCells, currCell.col_idx + 1);
    
    inputMap.at(currCell.row_idx).at(currCell.col_idx).character = '.';

    return stol(result);
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
            currVector.push_back(Cell(currRow, currCol, line[currCol]));
        }
        inputMap.push_back(currVector);
        currRow++;
    }

    for (int i = 0; i < currRow; i++) {
        for (int j = 0; j < currCol; j++) {
            result += returnValueIfHasAdjacentSymbol(inputMap, inputMap.at(i).at(j));
        }
    }

    cout << "Result is " << result;
}