#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <map>
#include <iterator>
#include <algorithm>

using namespace std;

int main () {

    ifstream file("tempFile.txt");
    if (!file.is_open()) {
        cerr << "Error opening file\n";
        return 1;
    }

    unordered_map<string, int> wordFrequency;
    string word;

    while (file >> word) {
        wordFrequency[word]++;
    }

    file.close();

    for (const auto &entry : wordFrequency) {
        cout << entry.first << " : " << entry.second << '\n';
    }

    // Move contents to a vector of pairs
    vector<pair<string, int>> wordFreqVec(wordFrequency.begin(), wordFrequency.end());
    // Sort the vector in descending order by frequency 
    // Sorts via a lambda funciton thats a little complicated and significantly reduces readability so probably try to make it a little simpler
    sort(wordFreqVec.begin(), wordFreqVec.end(), [](const pair<string, int> &a, const pair<string, int> &b) { return b.second < a.second; });


    //sort the myTokens in the decreasing order of VALUE which is frequencies

    for (const auto &entry : wordFrequency) {
        cout << entry.first << ' ';
    }

    cout << endl;
    cout << "********" << endl;


    //Now open the filename.text file again for reading
    //Read token by token as you have done this before

    //each time you get a token, find its position in the myTokens (sorted
    //data structure and print the position followed by space


    cout << endl;

    return 0;
}