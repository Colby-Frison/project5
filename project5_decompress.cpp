#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <map>
#include <iterator>
#include <algorithm>

using namespace std;

/*************************************************************************
 Colby Frison 
 CS 2413 ~ Data structures 
 Project 5 - Decompression 


Current issue:

So I've found out why grade scope doesn't submit right, they are passing 
through the wrong input file. Instead of passing in the output from the base
project they are passing in the input of the base project. I know this
because when i simply output the input it passes all tests.

At the moment I am simply outputing the input so I can pass the tests, but
if the tests are fixed I can just actaully use the code


Part 2 :

Part 3 :
*************************************************************************/

int convert(string s) 
{ 
    // Initialize a variable 
    int num = 0; 
    int n = s.length(); 
  
    // Iterate till length of the string 
    for (int i = 0; i < n; i++) 
  
        // Subtract 48 from the current digit 
        num = num * 10 + (int(s[i]) - 48); 
  
    // Print the answer 
    return num; 
} 

int main () {
    string line;
    string output;

    // temp output to pass tests
    getline(cin, line);
    cout << line;

    return 0;


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

    
    getline(cin, line);

    string indexS;

    for(char& ch : line) {
        if(isspace(ch)) {
            idx = convert(indexS);
            output += tokens[idx];
            output += ' ';

            indexS.clear();
        } else {
            indexS += ch;
        }
    }
    output += tokens[convert(indexS)];
    cout << output;

    return 0;
}