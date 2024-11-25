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
 Project 5 bonus - Decompression 

The instructions of this project say to take the output from the base 
project as the input for this part, but gradescope has it taking in the
plain text as input, we are then supposed to compress it and decompress it
in this code.

Compression can be looked over in the base project, this is essentially 
just a direct copy of what was done over there. The only difference is that
instead of outputing it saves all data to an output string which is then 
used by the decompression to work properly.

The decompression section of this is pretty simple, there are three lines 
to be read, the list of tokens, a dividing line, and the text represented 
as indexes of the sorted token map. Each of these lines have their own 
operation which is depicted in the code by operation 1 2 and 3.


Operation 1 creates the token map in token:index order

Operation 2 is not really needed, but it swaps the map to index:token order

operation 3 decompresses the line of indexes into words using the sorted 
token map

The specific detials of the logic is shown in the code

There is also a convert algorithm used to convert strings to integers, this
is used in operation 3 as an int is needed to access the map, and since 
integers cannot be extracted from strings directly this is what I settled
on. I tried using stoi() which worked in vscode, but for some reason this 
didn't work in gradescope so I found an alternative.

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

// -------------------------- Compression --------------------------------
    // The compression part is pretty much just a copy of the original 
    // base project, I just had to change how it was outputed so it could
    // still be read by the decompress part


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

    // clear any data from line so it can be used safely
    line.clear();

    string output2; // intiaize new final output

    map<string, int> tokensTemp; // map for collecting tokens and assigning index
    map<int, string> tokens; // map for fetching token from index

    // create indexes
    start = 0;
    size_t end2;

    //temp variables
    string token;
    int indexI = 1;

    // I had the code orgnaized one way, but then after realizing gradescope 
    // inputs the og input I had to make some changes, so now there are a 
    // series of if statments so It knows which operation to do for a given 
    // line. Line 1 = collect tokens. Line 2 is just the *** line so it isn't
    // really needed, but I'm using it to swap the map to the tokens one.
    // then line 3 = decompressing the text with the token indexes.
    // This could be optimized, but given the library and string constraints 
    // its good enough
    int operation = 0;


    while (start < output.length()) {
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

        // 1st operation: Collect tokens
        if (operation == 0) {
            
            //string word;
            for(char& ch : line) { // loop through line ch by ch

                // if the ch is a space then add token to map with val index
                // then increment index ad clear data from word
                if(isspace(ch)) {
                    tokensTemp[word] = indexI;
                    indexI++;

                    word.clear();
                } else { // add ch to word
                    word += ch;
                }
            }
        }

        // operation 2 : doesn't need to exist, but makes the code more readable (in my opinion)
        // simple swaps the map from => token:index to index:token
        if (operation == 1) {
            for (const auto &entry : tokensTemp) { 
                tokens.insert({entry.second, entry.first}); 
            }
        }

        // operation 3 : similar logic to opeartion 1, but instead of creating tokens
        // it uses the token to decompress the line.
        if(operation == 2) {

            int idx = -1; // initialize int index
        
            string indexS; // string index
            //this is needed as numbers are read as characters which are made to string
            // this string can then be converted to int for token fetching from map

            for(char& ch : line) { // same for loop as operation 1
                if(isspace(ch)) {
                    idx = convert(indexS); // convert string index to int
                    output2 += tokens[idx]; // fetch token and add to output
                    output2 += ' '; // add a space after each word

                    indexS.clear(); // clear string index
                } else {
                    indexS += ch; // add to word
                }
            }
            // handle last word
            output2 += tokens[convert(indexS)];
        }
        
        start = end2 + 1; // Move to the start of the next line
        operation++;
    }

    cout << output2;

    return 0;
}