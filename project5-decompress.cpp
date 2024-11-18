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

    //open file and ensure it actually opened
    ifstream tokenFile("tokens.txt");
    if (!tokenFile.is_open()) {
        cerr << "Error opening file\n";
        return 1;
    }

    string token;
    int index = 0;

    while (getline(tokenFile, token)){
        tokens[index++] = token;
    }
    tokenFile.close();
    
    //open file and ensure it actually opened
    ifstream compressedFile("compressedOutput.txt");
    if (!compressedFile.is_open()) {
        cerr << "Error opening file\n";
        return 1;
    }

    //open file and ensure it actually opened
    ofstream outputFile("decompressed.txt");
    if (!compressedFile.is_open()) {
        cerr << "Error opening file\n";
        return 1;
    }

    string line;


    char ch;
    string currentNumber;
    while (compressedFile.get(ch)) {
        if (isspace(ch)) {
            if(!currentNumber.empty()) {
                int idx = stoi(currentNumber);
                if(tokens.find(idx) != tokens.end()) {
                    outputFile << tokens[idx] << " ";
                } else {
                    cerr << "Error: index " << idx << " not found in tokens\n";
                    return 1;
                }
                currentNumber.clear();
            }
            if (ch == '\n') { 
                outputFile << '\n'; 
            }
        } else { 
            currentNumber += ch; 
        }
    }
    
    // Handle the last number if there is no trailing space 
    if (!currentNumber.empty()) { 
        int idx = stoi(currentNumber); 
        outputFile << tokens[idx] << " "; 
    } 
    
    compressedFile.close(); 
    outputFile.close();

    return 0;
}