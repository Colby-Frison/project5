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
 Project 5 - Compression 
**************************************************************************

Overall a pretty simple program, simply read a file, create a token based 
on the word read along with increasing the frequency of the token as it 
appears. Then this map is sorted in decreasing ordedr for faster acess. 
Finally the text file is read again and the words in the text file are 
assigned to an index of the token list hence encoding the text file. 

It should be just that simple, but since the gradescope only inputs the 
file once via redirected input, it not only doesnt do what the 
instructions, but since its only inputed once the string must be stored 
for the second read.

To handle this the each line is simply fed into the content string then 
it can be reread later in the file. It also says to read the file line 
by line, but the file is all in one line, so it kind of makes that 
obsolete.

In general though the program works by taking each character of the 
string and reconstructing words, if the charcter is a space, it knows
the words is over, so it does its operations, clears the word and moves 
on.

Also the sorting of the list is done through a mutlimap with a greater 
parameter. Its kinda convoluted how this is organized, as it goes from
unordered map to map to multimap back to a map.

Lastly the second time reading through the "file" it uses a slighly 
different for and while loop along with a few extra if statements
since it has to handle a normal string instead of just being able to use 
the input methods.

**************************************************************************
LLM Documentation :

Debugging and Testing Plan :

*************************************************************************/
int main () {
    string fileContent; // To store the entire file as a string
    string line; // to store each line

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
                    cout << wordIndex[word] << " ";
                    word.clear();
                }
            } else {
                word += ch; // add char to word
                
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


/*************************************************************************
 *** LLM Documentation ***
**************************************************************************

In this project there was very limited usage of LLMs. This project as 
shown from the limited code is quite simple. The main issues I encountered 
wasmainly due the the way files were inputed. At first I was under the 
assumption we would be reading a txt file, but then I swapped to a simple 
inputand finaly redirected input. These changes in inputs caused a lot of
issues when trying to figure out how to orgnaize things like while loops, 
and even simply how to take in each token/line. These were all different 
as I had to go from simply reading word by word to line by line to iterating
through all characters and building the words from their character. So with
that the only usage of AI I really had was how to deal with the inputs. 
Unfortunatley Chat-gpt updated their website and the chat I used to discuss 
redirected input is no longer accessable in full. The main idea though
is I asked what the syntax "./a.out < filename.txt" did and how do I read 
from it. Which it responded its just redirected input, and it can be read 
using cin. I also asked if I'm using a while loop to read it, how does it 
know when to stop. Which it responded it automatically stops when the file 
is finished being read. But thats pretty much it for LLM usage. I did do 
some research on maps and sorting maps elsewhere so I could actually figure 
out how to use a map, and do so somewhat efficiently. I also did some 
research on compression efficency, only to find that this method is wildly 
inefficient, and for this type of text it is not very efficient in 
compression, but thats unimportant.

So in the end, I've provided the few prompts I've used above along with a 
rough response, the rational of said prompts were somewhat explained, (I 
was trying to figure out how redirected input was working). Lastly, the 
third part is not very applicable since I only used the LLM to solve one 
problem, and not a sequence of problems.

**************************************************************************
 *** Debugging and Testing Plan ***
**************************************************************************

Specific Tests
    There were a few tests I used to make sure the program was working 
    properly. The first of which was simply comparing my output with the 
    output provided in the project description. This was helpful when 
    comapring final results, but not very helpful when searching for 
    specific problems, which is where the next technique came in. The next
    testing method was series of debug statments, due to the simplicity 
    of this progrma there wasn't a need for a lot of debugging, but I did 
    use them to make sure stuff like tokens frequencies and indexes were 
    all ebing assigned correctly, I also used debug statements when testing 
    with inputs to make sure the way I was reading ti was actually correct. 
    The final way I debugged was by essetially using gradescope as a 
    compiler. When all of my tests worked I went to gradescope to submit 
    only to find ti said I was wrong, which was wierd because my tests said 
    otherwise. So I then made itterations in my program and kept submitting 
    to gradescope until the desired result was achieved. This was very 
    monotonous and not very useful since gradescope doesn't really give a 
    usefull debug output, it kind of does, but in all honesty it isn't all 
    the helpful. But this method had to be done since there really isn't any 
    other way to test the program the exact same way gradescope does without 
    actually having acess to the testing program.

Issues and Resolutions
    One issue I remember encountering was when printing indexes I would be 
    missing a value and a value would be 0 instead of the proper index, this 
    took a very long time to figure out even though it should have been a 
    quick fix. I initially though a token wasn't beign assigned properly so
    I went through the process of checking that every token was accounted 
    for and assigned a proper frequency, along with that I made sure that when
    maps were being swapped, everything worked, or that everything was 
    sorted properly. This came back with no errors so I moved on to the next 
    potential trouble area which was reading through the 'file' a second 
    time. This was a simple check by just printing out each line as it was 
    parsed, this also had no issue. The last area to check was the word 
    builder the second time. This is where the issue was, I found that when 
    going through the last word there was no trailing space, so the final 
    word was not outputed which was the aformentioned missing word, this word 
    was not cleared so when going to the first word of the next line there 
    extra character that obviously didn't have a token so it defaulted to 0.
    To solve this issue I put in a small check that saw if the index of 
    the current iteration is the last index of the string 'line', if it was the 
    index of that word was printed out and the word was cleared. This resolved 
    the issue, and although it was a very simple issue it unfortunately
    took a little bit to find.

Verification
    This category seems to be more important for other projects than for this 
    one since we are actually making the main method for this one. But 
    regardless I gues thiss section pertains to being able to stick to the 
    format of the project description and ensuring only the permitted 
    libraries were utilized, but thats quite eacy to do. The only difference 
    in my method compared to the main method is opening and closing the 
    file, I'm not sure if this is actually needed, but since it differes from 
    the project instructions I feel it is important to point out.
    Other than that verfifiction of proper function of the program is described 
    in the specific tests section.


**************************************************************************/