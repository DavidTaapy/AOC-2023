#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <algorithm>
#include <set>

using namespace std;

long long calculateTotalWinnings(vector<pair<string, long long>> cardBidVector);
bool compareHandsReverse(pair<string, long long> handOne, pair<string, long long> handTwo);
int determineCardType(string);
int determineCardTypeWithCardFreq(unordered_map<char, int> cardFreq);
string replaceChar(string origString, char toReplace, char replacement);
pair<set<char>, unordered_map<char, int>> getCardInfo(string cards);

unordered_map<char, int> cardValDict = {
        {'2', 1}, {'3', 2}, {'4', 3}, {'5', 4}, {'6', 5}, {'7', 6}, {'8', 7}, {'9', 8},
        {'T', 9}, {'J', 0}, {'Q', 11}, {'K', 12}, {'A', 13}
};

bool compareHandsReverse(pair<string, long long> handOne, pair<string, long long> handTwo) {
    string cardOne = handOne.first;
    string cardTwo = handTwo.first;

    int typeOne = determineCardType(cardOne);
    int typeTwo = determineCardType(cardTwo);

    if (typeOne < typeTwo) return true;
    else if (typeTwo < typeOne) return false;
    else {
        for (int i = 0; i < cardOne.size(); i++) {
            if (cardOne[i] == cardTwo[i]) continue;
            else return cardValDict[cardOne[i]] < cardValDict[cardTwo[i]];
        }
    }
}

long long calculateTotalWinnings(vector<pair<string, long long>> cardBidVector) {
    sort(cardBidVector.begin(), cardBidVector.end(), compareHandsReverse);

    long long result = 0;
    for (int i = 0; i < cardBidVector.size(); i++) {
        result += cardBidVector[i].second * (i + 1);
    }
    return result;
}

int determineCardType(string cards) {
    pair<set<char>, unordered_map<char, int>> cardInfo = getCardInfo(cards);
    set<char> presentChars = cardInfo.first;
    unordered_map<char, int> cardFreq = cardInfo.second;

    if (presentChars.find('J') == presentChars.end()) return determineCardTypeWithCardFreq(cardFreq);
    else {
        int bestCardType = 0;
        for (char possCard : presentChars) {
            string replacedCards = replaceChar(cards, 'J', possCard);
            pair<set<char>, unordered_map<char, int>> cardInfo = getCardInfo(replacedCards);
            set<char> presentChars = cardInfo.first;
            unordered_map<char, int> cardFreq = cardInfo.second;

            int cardType = determineCardTypeWithCardFreq(cardFreq);
            if (cardType > bestCardType) bestCardType = cardType;
        }

        return bestCardType;
    }
}

pair<set<char>, unordered_map<char, int>> getCardInfo(string cards) {
    unordered_map<char, int> cardFreq;
    set<char> presentChars;
    for (int i = 0; i < cards.size(); i++) {
        char card = cards[i];
        cardFreq[card]++;
        presentChars.insert(card);
    }

    return make_pair(presentChars, cardFreq);
}

string replaceChar(string origString, char toReplace, char replacement) {
    string copyString = origString;
    for (int i = 0; i < copyString.size(); i++) {
        if (copyString[i] == toReplace) copyString[i] = replacement;
    }

    return copyString;
}

int determineCardTypeWithCardFreq(unordered_map<char, int> cardFreq) {
    if (cardFreq.size() == 1) return 7;
    else if (cardFreq.size() == 2) {
        int firstVal = cardFreq.begin()->second;
        if (firstVal == 1 || firstVal == 4) return 6;
        else return 5;
    }
    else if (cardFreq.size() == 3) {
        for (auto pair : cardFreq) {
            if (pair.second == 3) return 4;
        }
        return 3;
    }
    else if (cardFreq.size() == 4) return 2;
    else return 1;
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
    vector<pair<string, long long>> cardBidVector;
    while (getline(myFile, line)) {
        string card, bid;
        istringstream iss(line);

        iss >> card;
        iss >> bid;
        cardBidVector.push_back(make_pair(card, stoll(bid)));
    }

    result = calculateTotalWinnings(cardBidVector);

    cout << "Result is " << result;
}