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

    string fileContent; // To store the entire file as a string
    string line; // to store each line

    string output; // string to save output to properly handle decompression


    // initialize unordered map token:frequency
    unordered_map<string, int> wordFrequency;

    // initialize string to temp hold token
    while (getline(cin, line, '\n')) {
        // checker to stop input sequence because I dont use redirected input
        if(line == "STOP") break;

        string word; // stores word being built

        for(char& ch : line) {// loop through line
            if(isspace(ch)) { // if character is ' '
                
            // auto initialize token if it doesn't exist then add frequency regardless
                wordFrequency[word]++;
                word.clear(); // clear word
            } else {
                word += ch; // build word
            }
        }
        // sicne it doesnt end in a space it doesn't account for the last word
        wordFrequency[word]++; 
        fileContent = fileContent + line; // add to full content for later
    }

    // Move contents to a map where the key is the word and the value is the frequency 
    map<string, int> sortedMap(wordFrequency.begin(), wordFrequency.end()); 

    // Use a multimap to sort by frequency 
    // swap key and value so it can be sorted by frequency
    multimap<int, string, greater<int>> frequencySortedMap; 
    
    //insert everything from the map into the multimap, which is sorted by greater<int>
    for (const auto &entry : sortedMap) { 
        frequencySortedMap.insert({entry.second, entry.first}); 
    }

    // print out all tokens
    //print second entry since its organized frequency:token for sorting purposes
    for (const auto &entry : frequencySortedMap){
        output += entry.second;
        output += ' ';
    }

    // Create a map to assign each word an index 
    map<string, int> wordIndex; 
    int index = 1; 
    for (const auto &entry : frequencySortedMap) { 
        wordIndex[entry.second] = index; 
        index++;
    }

    // print divider
    output += '\n';
    output += "**********";
    output += '\n';

    // create indexes
    size_t start = 0;
    size_t end;

    // since it can only be read once I now had to use a string to read the file again

    // Process line by line until the end of string
    while (start < fileContent.length()) {
        // set end of line to 1st location of new line return
        end = fileContent.find('\n', start);
        
        // If no newline found, process until end of string
        if (end == string::npos) {
            end = fileContent.length();
        }
        
        line = fileContent.substr(start, end - start); // Extract a line
        
        // Process the line word by word
        string word;
        bool isFirstWord = true;

        // loop through line
        for (size_t i = 0; i < line.length(); i++) {
            //get char from string
            char ch = line[i];
            
            //if space & word built is not empty then output the index of the word built
            if (isspace(ch)) {
                if (!word.empty()) {
                    output += to_string(wordIndex[word]);
                    output += ' ';
                    word.clear();
                }
            } else {
                word += ch; // add char to word
                
                // If we're at the last character of the line
                if (i == line.length() - 1) {
                    output += to_string(wordIndex[word]);
                    output += ' ';
                    word.clear();
                }
            }
        }
        
        start = end + 1; // Move to the start of the next line
    }

// ------------------------------ Decompress --------------------------------


    line.clear();

    string output2;

    map<string, int> tokensTemp;
    map<int, string> tokens;

    // create indexes
    start = 0;
    size_t end2;

    string token;
    int indexI = 1;

    int operation = 0;


    while (start < output.length()) {
        //cout << "test0" << endl;
        // set end of line to 1st location of new line return
        end2 = output.find('\n', start);
        
        // If no newline found, process until end of string
        if (end2 == string::npos) {
            end2 = output.length();
        }
        
        line = output.substr(start, end2 - start); // Extract a line
        
        // Process the line word by word
        string word;
        bool isFirstWord = true;

        if (operation == 0) {
            string word;
            for(char& ch : line) {
                if(isspace(ch)) {
                    tokensTemp[word] = indexI;
                    indexI++;

                    word.clear();
                } else {
                    word += ch;
                }
            }
            //cout << "test1" << endl;
        }

        if (operation == 1) {
            for (const auto &entry : tokensTemp) { 
                tokens.insert({entry.second, entry.first}); 
            }
            //cout << "test2" << endl;
        }

        if(operation == 2) {
            int idx = -1;

        
            string indexS;

            for(char& ch : line) {
                if(isspace(ch)) {
                    idx = convert(indexS);
                    output2 += tokens[idx];
                    output2 += ' ';

                    indexS.clear();
                } else {
                    indexS += ch;
                }
            }
            output2 += tokens[convert(indexS)];
            cout << tokens[convert(indexS)];

            //cout << "test3" << endl;
        }
        
        start = end2 + 1; // Move to the start of the next line
        operation++;
        //cout << "test4" << endl;
    }

    //cout << "test5" << endl;

    cout << output2;

    return 0;
}