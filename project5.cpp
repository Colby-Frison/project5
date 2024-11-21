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
************************************************************ Project 5 - Compression ***************************************************************
****************************************************************************************************************************************************

Overall a pretty simple program, simply read a file, create a token based on the word read along with increasing the frequency of 
the token as it appears. Then this map is sorted in decreasing ordedr for faster acess. Finally the text file is read again and the 
words in the text file are assigned to an index of the token list hence encoding the text file. 

It should be just that simple, but since the gradescope only inputs the file once via redirected input, it not only doesnt do what 
the instructions, but since its only inputed once the string must be stored for the second read.

To handle this the each line is simply fed into the content string then it can be reread later in the file. It also says to read the 
file line by line, but the file is all in one line, so it kind of makes that obsolete.

In general though the program works by taking each character of the string and reconstructing words, if the charcter is a space, it knows
the words is over, so it does its operations, clears the word and moves on.

Also the sorting of the list is done through a mutlimap with a greater parameter. Its kinda convoluted how this is organized, as it goes from
unordered map to map to multimap back to a map.

Lastly the second time reading through the "file" it uses a slighly different for and while loop along with a few extra if statements
since it has to handle a normal string instead of just being able to use the input methods.

****************************************************************************************************************************************************

Part 2 :

Part 3 :

***************************************************************************************************************************************************/
int main () {
    string fileContent; // To store the entire file as a string
    string line; // to store each line

    // initialize unordered map token:frequency
    unordered_map<string, int> wordFrequency;

    // initialize string to temp hold token
    while (getline(cin, line, '\n')) {
        if(line == "STOP") break; // checker to stop input sequence because I dont use redirected input

        string word; // stores word being built

        for(char& ch : line) {// loop through line
            if(isspace(ch)) { // if character is ' '
                wordFrequency[word]++; // auto initialize token if it doesn't exist then add frequency regardless
                word.clear(); // clear word
            } else {
                word += ch; // build word
            }
        }
        wordFrequency[word]++; // sicne it doesnt end in a space it doesn't account for the last word
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
        cout << entry.second << ' ';
    }

    // Create a map to assign each word an index 
    map<string, int> wordIndex; 
    int index = 1; 
    for (const auto &entry : frequencySortedMap) { 
        wordIndex[entry.second] = index; 
        index++;
    }

    // print divider
    cout << endl;
    cout << "**********" << endl;

    // create indexes
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