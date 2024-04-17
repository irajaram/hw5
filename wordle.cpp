#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


void wordleHelper(
                const std::string& fixedChar, 
                std::string floatChar, 
                const std::set<std::string>& dict, 
                std::set<std::string>& res, 
                std::string& currWord, 
                int j,
                int dashCount);

// Definition of primary wordle function
std::set<std::string> wordle(const std::string& in, const std::string& floating, const std::set<std::string>& dict) {
    // Add your code here
    set<string> res;
    string currWord(in); //initialize string to store generated words and initialized to size of input using reference from cplusplus.com
    int j =0;
    string floatChar = floating;
    // Call the recursive helper function for each position
    /*for(char c: floating){
      cout << c << " " << endl;
    }*/
    int dashCount =0;
    for(int i=0; i<currWord.size(); i++){
      if(currWord[i]=='-'){
        ++dashCount;
      }
    }
    wordleHelper(in, floatChar, dict, res, currWord, j, dashCount);

    return res;
}

// Define any helper functions here
void wordleHelper(const std::string& fixedChar, std::string floatChar, const std::set<std::string>& dict, std::set<std::string>& res, std::string& currWord, int j, int dashCount) {
    //cout << "Processing word: " << currWord << endl;
    if (j == fixedChar.size()) {
        if (dict.find(currWord) != dict.end() && floatChar.size() == 0) {
            //cout << "Found word in dictionary: " << currWord << endl;
            res.insert(currWord);
        } 
        else {
          //cout << "Word not found in dictionary: " << currWord << endl;
        }
        return;
    }
    
    if (currWord[j] != '-') {
      //cout << "reaching first" << endl;
      wordleHelper(fixedChar, floatChar, dict, res, currWord, j + 1, dashCount);
    } 

    else {
      if (dashCount <= floatChar.size()) {
        string temp = floatChar;
        for (int i=0; i<floatChar.size(); i++) {
          char letter = floatChar[i];
          currWord[j] = letter;
          floatChar.erase(floatChar.find(letter),1);
          wordleHelper(fixedChar, floatChar, dict, res, currWord, j+1, dashCount-1);
          floatChar = temp;
        }
      }

      else {
        //issue not entering here
        //cout << "reached this point" << endl;
        for (char c = 'a'; c <= 'z'; ++c) {
          string temp = floatChar;
          if(floatChar.find(c)!=string::npos){
            floatChar.erase(floatChar.find(c),1);
          }
          currWord[j] = c;
          wordleHelper(fixedChar, floatChar, dict, res, currWord, j+1, dashCount -1);
          floatChar = temp;
        }
      }
      currWord[j] = '-';
    }
}