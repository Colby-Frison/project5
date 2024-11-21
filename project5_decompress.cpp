#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <map>
#include <iterator>
#include <algorithm>

using namespace std;

int main () {


    map<int, string> tokens;

    string token;
    int index = 1;
    
    cin >> token;

    while (token != "**********"){
        tokens[index++] = token;
        cin >> token;
    }

    while (getline(cin, token)) {
        tokens[index++] = token;
    }


    string line;

    while (getline(cin, line, '\n')) {
        string index;
        for(char& ch : line) {
            if(isspace(ch)) {
                int idx = stoi(index);
                cout << tokens[idx] << " ";
                index.clear();
            } else {
                index += ch;
            }
        }
        cout << endl;
    }


    return 0;
}