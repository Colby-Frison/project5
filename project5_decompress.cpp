#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <map>
#include <iterator>
#include <algorithm>

using namespace std;

/***************************************************************************************************************************************************
***************************************************************** Colby Frison *********************************************************************
*********************************************************** CS 2413 ~ Data structures **************************************************************
*********************************************************** Project 5 - Decompression **************************************************************
****************************************************************************************************************************************************


Part 2 :

Part 3 :
***************************************************************************************************************************************************/

int main () {
    string line;


    map<string, int> tokensTemp;

    string token;
    int index = 1;


    getline(cin, line);

    string word;
    for(char& ch : line) {
        if(isspace(ch)) {
            tokensTemp[word] = index;
            index++;

            word.clear();
        } else {
            word += ch;
        }
    }

    getline(cin, line);

    map<int, string> tokens;
    for (const auto &entry : tokensTemp) { 
        tokens.insert({entry.second, entry.first}); 
    }

    line.clear();

    int idx = -1;

    
    while (getline(cin, line)) {
        string index;
        for(char& ch : line) {
            if(isspace(ch)) {
                idx = stoi(index);
                cout << tokens[idx] << " ";
                index.clear();
            } else {
                index += ch;
            }
        }
        cout << tokens[stoi(index)];
    }


    return 0;
}