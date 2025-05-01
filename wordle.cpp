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
void wordlehelper( const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict, const std::map<int, std::set<char>>& possible, 
    std::string& current, int index, std::set<std::string>& result);


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    int size = in.size();
    std::map<int, std::set<char>> possible; //will store all possible letters

    for(std::set<std::string>::const_iterator it = dict.begin(); it != dict.end(); it++){ //loops through all possible words
        const std::string& temp = *it;
        if(temp.size() != size){ //if the word is the wrong size then we skip it
        }
        else{
            bool fixed = true;
            for(int i = 0; i < size; i++){ // this checks to see if all the fixed letters from in are in our dict word where theyre supposed to be
                if(in[i] != '-' && temp[i] != in[i]){
                    fixed = false;
                    break;
                }
            }
            if (fixed){
                for(int i = 0; i < size; i++){
                    if(in[i] == '-'){
                        char c = temp[i];
                        if(std::islower(c)){
                           possible[i].insert(c);
                        }
                    }
                }
            }
        }
    }
    std::set<std::string> result;
    std::string current = in;
    wordlehelper(in, floating, dict, possible, current, 0, result);
    return result;

}

// Define any helper functions here
void wordlehelper( const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict,
    const std::map<int, std::set<char>>& possible,
    std::string& current, 
    int index, 
    std::set<std::string>& result)
    {
        int size = in.size();
        if (index == size){ //base case
            std::string temp = current;
            for(int i = 0; i < floating.size(); i++){
                char tmp = floating[i];
                if(temp.find(tmp) == std::string::npos){ //situation where full test word doesn't include floating letters
                    return;
                }
                temp[temp.find(tmp)] = '-'; //gets rid of duplicates after we check
            }
            
            if(dict.find(current) != dict.end()){ // check to see if word is in dictionary
                result.insert(current);
            }
            return;
        }

        if(in[index] != '-'){ //if there is already a fixed letter in this slot
            wordlehelper(in, floating, dict, possible, current, index + 1, result);
        }

        else{
            const std::set<char>& choice = possible.at(index);
            for(std::set<char>::const_iterator it = choice.begin(); it != choice.end(); it++){ //tests all combinations
                current[index] = *it;
                wordlehelper(in, floating, dict, possible, current, index + 1, result);
            }
            current[index] = '-';
        }

    }
