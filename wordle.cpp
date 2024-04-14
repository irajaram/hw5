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


// Add prototypes of helper functions here

void wordleHelper(const std::string& fixedChar, const std::string& floatChar, const std::set<std::string>& dict, std:: set<std::string>& res, std::string& currWord, int& j);
// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    set<string> res;
    string currWord(in.size(),'-'); //initialize string to store generated words and initialized to size of input using reference from cplusplus.com
    for(int i = 0; i< currWord.size(); i++){
        wordleHelper(in, floating, dict, res, currWord, i);
    }

    return res;




}

// Define any helper functions here
void wordleHelper(const std::string& fixedChar, const std::string& floatChar, const std::set<std::string>& dict, std:: set<std::string>& res, std::string& currWord, int& j){
    if(j == currWord.size()){
        if(dict.find(currWord)!= dict.end()){
        res.insert(currWord);
        }
        return;
    }
    else if(currWord[j]!='-'){
        currWord[j] = fixedChar[j];
        wordleHelper(fixedChar,floatChar,dict,res,currWord, j+1);
    }
    else{ 
        for(int i=0; i<floatChar.size(); i++){
            currWord[j] = floatChar[i];
            wordleHelper(fixedChar, floatChar, dict,res, currWord, j+1);
        }
    }
    currWord[j] = '-';
}