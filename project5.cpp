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
    string fileName;

    cin >> fileName;
    

    //open file and ensure it actually opened
    ifstream file("tests/input3.txt");
    if (!file.is_open()) {
        cerr << "Error opening file\n";
        return 1;
    }

    // initialize unordered map token:frequency
    unordered_map<string, int> wordFrequency;

    // initialize string to temp hold token
    string word;


    /***  File is read and the next word is inserted into the map, if it doesnt exist it makes it automatically
    and adds to it. If it already exists it simply adds one to the frequency. The while loop works because it 
    throws a true if the file is properly read and false if there is nothign read. ***/
    while (file >> word) {
        wordFrequency[word]++;
    }

    // after finsihed reading file is closed
    file.close();

    // Move contents to a map where the key is the word and the value is the frequency 
    map<string, int> sortedMap(wordFrequency.begin(), wordFrequency.end()); 

    // Use a multimap to sort by frequency 
    // swap key and value so it can be sorted by frequency
    multimap<int, string, greater<int>> frequencySortedMap; 
    
    //insert everything from the map into the multimap, which is sorted by greater<int>
    for (const auto &entry : sortedMap) { 
        frequencySortedMap.insert({entry.second, entry.first}); 
    }

    // Reopen the file to find the index of each word and print it 
    file.open("tests/input3.txt"); 
    if (!file.is_open()) { 
        cerr << "Error reopening file\n"; return 1; 
    } 

    // Create a map to assign each word an index 
    map<string, int> wordIndex; 
    int index = 1; 
    for (const auto &entry : frequencySortedMap) { 
        wordIndex[entry.second] = index; 
        index++;
    } 

    for (const auto &entry : frequencySortedMap){
        cout << entry.second << ' ';
    }

    cout << endl;
    cout << "**********" << endl;

    string line;
    while (getline(file, line, '\n')) {
        string word;
        for(char& ch : line) {
            if(isspace(ch)) {
                cout << wordIndex[word] << " ";
                word.clear();
            } else {
                word += ch;
            }
        }
        cout << wordIndex[word] << " ";        
        /*
        cout << endl;
        outputFile << '\n';
        */
    }
    
    file.close(); 

    cout << endl;

    return 0;
}