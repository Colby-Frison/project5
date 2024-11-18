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


    //read the name of the file ./a.out < filename.txt

    //get each token and store them in the unordered_map (or map) increment
    //its frequencies. You MAY be able to do myTokens[aToken]++. Work on this.

    //close the file (filename.txt)


    //sort the myTokens in the decreasing order of VALUE which is frequencies

    //print the KEYS in myTokens (which has been sorted)separated by a space.
    //after you printed the KEYS Do this
    cout << endl;
    cout << "********" << endl;


    //Now open the filename.text file again for reading
    //Read token by token as you have done this before

    //each time you get a token, find its position in the myTokens (sorted
    //data structure and print the position followed by space


    cout << endl;

    return 0;
}