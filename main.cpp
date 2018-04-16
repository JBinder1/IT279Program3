#include <cstdlib>
#include <fstream>
#include <queue>
#include <utility>

#include "Dictionary.h"

using namespace std;

const string dictionaryFilename = "dict.txt";
ifstream inputFile;

/*
 * Populates the Dictionary with the contents of dict.txt.
 * Each word in dict.txt must be on its own line.
 * The dictionary is case insensitive.
 */
int populateDictionary(Dictionary & dict){
    inputFile.open(dictionaryFilename);
    if(inputFile.is_open()){
        string inputLine;
        while(getline(inputFile, inputLine)){
            inputLine[0] = tolower(inputLine[0]);       // Ensures case insensitivity by storing all dictionary words as lowercase
            if(!dict.FindEntry(inputLine)){         // If the word isn't already in the Dictionary,
                dict.AddEntry(inputLine);           // add it to the Dictionary.
            }
        }
        inputFile.close();
        return 0;
    }else{
        cout<<"Unable to open dictionary. Please make sure "<<dictionaryFilename<<" is in this directory.";
    }
    return -1;
}

/*
 * Tests if a word will be in the Dictionary if any one letter is inserted at any point.
 * If so, it adds it to the possibleWords queue for that word.
 */
void testAdd(string word, Dictionary & dict, queue<string> & possibleWords){
    string temp = word;
    for(int i = 0; i < word.length(); i++){
        for(char letter = 'a'; letter <= 'z'; letter++){
            temp.insert(i, 1, letter);
            if(dict.FindEntry(temp)){
                possibleWords.push(temp);
            }
            temp = word;    // resets value of temp for the next loop
        }
    }
}

/*
 * Tests if a word will be in the Dictionary if any one letter is removed from it.
 * If so, it adds it to the possibleWords queue for that word.
 */
void testRemove(string word, Dictionary & dict, queue<string> & possibleWords){
    string temp = word;
    for(int i = 0; i <= word.length(); i++){
        temp.erase(i, 1);           // Erases a character at position i of the word
        if(dict.FindEntry(temp)){       // If the result is in the dictionary, 
            possibleWords.push(temp);   // add it to the list that'll be returned
        }
        temp = word;                    // Resets value of temp for the next loop
    }
}

/*
 * Tests if a word will be in the Dictionary if any two adjacent letters are swapped.
 * If so, it adds it to the possibleWorlds queue for that word.
 */
void testSwap(string word, Dictionary & dict, queue<string> & possibleWords){
    string temp = word;
    char j;
    for(int i = 0; i < word.length() - 1; i++){
        j = temp[i];                    // Swaps character i with character i+1
        temp[i] = temp[i+1];
        temp[i+1] = j;
        if(dict.FindEntry(temp)){       // If the result is in the dictionary, 
            possibleWords.push(temp);   // add it to the list that'll be returned
        }
        temp = word;                    // Resets value of temp for the next loop
    }
}

/*
 * Attempts to open the file. If it fails, the program ends. If it succeeds,
 * this method reads a word off of each line, checks for it in the Dictionary,
 * and if it is not present, runs testAdd, testRemove, and testSwap to fill
 * the possibleWords queue with possible corrections.
 * Then it prints the content of possibleWords and moves on to the next line.
 */
int readFile(string inputFileName, Dictionary & dict, queue<string> & possibleWords){
    inputFile.open(inputFileName);
    if(inputFile.is_open()){
        cout<<"File opened!\n\n";
        string inputLine;
        int lineCount = 1;  // Keeps track of which line each typo is found on
        while(getline(inputFile, inputLine)){
            inputLine[0] = tolower(inputLine[0]);       // Ensures case-insensitivity by reading all lines as lowercase
            if(inputLine[inputLine.length() - 1] == ' ')        // If the last character of the string is a space,
                inputLine.erase(inputLine.length() - 1, 1);     // erase the last character.
            if(dict.FindEntry(inputLine) == 0){
                testAdd(inputLine, dict, possibleWords);
                testRemove(inputLine, dict, possibleWords);
                testSwap(inputLine, dict, possibleWords);
                cout<<"Typo found on line "<<lineCount<<": "<<inputLine<<"\nPossible alternatives:\n";
                while(!possibleWords.empty()){          // Prints each possible word the test methods found
                    cout<<possibleWords.front()<<endl;
                    possibleWords.pop();
                }
                cout<<endl;
            }
            lineCount++;
        }
        inputFile.close();
        return 0;
    }else{
        cout<<"Unable to open your file. Please make sure "<<inputFileName<<" is in this directory.";
        return -1;
    }
}

int main(int argc, char** argv) {
    Dictionary dict;
    queue<string> possibleWords;
    string inputFileName;
    
    if(populateDictionary(dict) == -1)
        return -1;
    
    cout<<"Please enter the name of the .txt file you wish to spellcheck:\n";
    cin>>inputFileName;
    if(readFile(inputFileName, dict, possibleWords) == -1)
        return -1;
    
    return 0;
}