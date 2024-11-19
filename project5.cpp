#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <map>
#include <iterator>
#include <algorithm>

using namespace std;

int main () {

    //open file and ensure it actually opened
    ifstream file("tempFile.txt");
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

    // the entire unorderedMap is then printed as token:frequency
    for (const auto &entry : wordFrequency) {
        cout << entry.first << " : " << entry.second << '\n';
    }

    cout << ":::::::::::::::::::::::::" << endl;


    // Move contents to a map where the key is the word and the value is the frequency 
    map<string, int> sortedMap(wordFrequency.begin(), wordFrequency.end()); 

    // Use a multimap to sort by frequency 
    // swap key and value so it can be sorted by frequency
    multimap<int, string, greater<int>> frequencySortedMap; 
    
    //insert everything from the map into the multimap, which is sorted by greater<int>
    for (const auto &entry : sortedMap) { 
        frequencySortedMap.insert({entry.second, entry.first}); 
    }

    // the entire list is then printed as token:frequency
    for (const auto &entry : frequencySortedMap) {
        cout << entry.second << " : " << entry.first << '\n';
    }

    /*

    // print the tokens from the multimap seperated by a space
    // this is in decreasing order of frequency
    for (const auto &entry : frequencySortedMap) {
        cout << entry.second << ' ';
    }

    */

    cout << endl;
    cout << "********" << endl;

    // Reopen the file to find the index of each word and print it 
    file.open("tempFile.txt"); 
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

    // Open the output file 
    ofstream outputFile("compressedOutput.txt"); 
    if (!outputFile.is_open()) { 
        cerr << "Error opening output file\n"; 
        return 1;
    }

    ofstream tokenFile("tokens.txt"); 
    if (!outputFile.is_open()) { 
        cerr << "Error opening output file\n"; 
        return 1;
    }

    for (const auto &entry : frequencySortedMap){
        tokenFile << entry.second << '\n';
    }

    string line;
    while (getline(file, line, '\n')) {
        string word;
        for(char& ch : line) {
            if(isspace(ch)) {
                cout << wordIndex[word] << " ";
                outputFile << wordIndex[word] << " ";
                word.clear();
            } else {
                word += ch;
            }
        }
        cout << endl;
        outputFile << '\n';
    }

    /*

    // Read the file again and print the corresponding index of each word 
    char ch; 
    string currentWord; 
    while (file.get(ch)) { 
        if (isspace(ch)) { 
            if (!currentWord.empty()) { 
                cout << wordIndex[currentWord] << " "; 
                outputFile << wordIndex[currentWord] << " "; 
                currentWord.clear(); 
            } 
            if (ch == '\n') { 
                cout << '\n'; 
                outputFile << '\n'; 
            } 
        } else { 
            currentWord += ch; 
        } 
    } 
    if (!currentWord.empty()) { // handle the last word if there is no trailing space
        cout << wordIndex[currentWord] << " "; 
        outputFile << wordIndex[currentWord] << " "; 
    } 

    */
    
    file.close(); 
    outputFile.close();

    cout << endl;

    return 0;
}