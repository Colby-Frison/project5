#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <map>
#include <iterator>
#include <algorithm>

using namespace std;


/*
Colby Frison
CS 2413 ~ Data structures
Project 5 - Compression

Overall a pretty simple program, simply read a file, create a token based on the word read along with increasing the frequency of 
the token as it appears. Then this map is sorted in decreasing ordedr for faster acess. Finally the text file is read again and the 
words in the text file are assigned to an index of the token list hence encoding the text file. 

This type of encoding is not very efficient when working with a file that does not posses much repetition as it relies on the repetition
of words to decrease the file size. In all of the text files provided they do not contain much if any repetition so the compression and 
decompression actaully makes it less space efficient. To remedy this a different form of compression could be used
*/
int main () {
    string fileContent; // To store the entire file as a string
    string line;

    // initialize unordered map token:frequency
    unordered_map<string, int> wordFrequency;

    // initialize string to temp hold token
    while (getline(cin, line, '\n')) {
        if(line == "STOP") break;
        string word;
        for(char& ch : line) {
            if(isspace(ch)) {
                wordFrequency[word]++;
                word.clear();
            } else {
                word += ch;
            }
        }
        wordFrequency[word]++;
        fileContent = fileContent + line;
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

    for (const auto &entry : frequencySortedMap){
        cout << entry.second << ' ';
    }

    // Create a map to assign each word an index 
    map<string, int> wordIndex; 
    int index = 1; 
    for (const auto &entry : frequencySortedMap) { 
        wordIndex[entry.second] = index; 
        index++;
    }


    cout << endl;
    cout << "**********" << endl;

    size_t start = 0;
    size_t end;

    // Process lines until the end of string
    while (start < fileContent.length()) {
        end = fileContent.find('\n', start);
        
        // If no newline found, process until end of string
        if (end == string::npos) {
            end = fileContent.length();
        }
        
        line = fileContent.substr(start, end - start); // Extract a line
        
        // Process the line word by word
        string word;
        bool isFirstWord = true;

        for (size_t i = 0; i < line.length(); i++) {
            char ch = line[i];
            
            if (isspace(ch)) {
                if (!word.empty()) {
                    cout << wordIndex[word] << " ";
                    word.clear();
                }
            } else {
                word += ch;
                
                // If we're at the last character of the line
                if (i == line.length() - 1) {
                    cout << wordIndex[word] << " ";
                    word.clear();
                }
            }
        }
        
        start = end + 1; // Move to the start of the next line
    }

    cout << endl;

    return 0;
}