#include <string>
#include <iostream>
#include <unordered_map>
#include <cstring>
#include <algorithm>

std::string cannonical(const std::string input) {
    std::sort(input.begin(), input.end())
    return input;
}

//read next word
bool get_next_word(std::string& curword) {
    curword.clear();
    if (!std::cin) return false;
    char curchar;
    //while there's nonalphanumeric characters, ignore
    while(std::cin.get(curchar) && isalnum(curchar)==false)
        ;
    //if we got an alphanumeric, store it
    if (std::cin) 
        curword += tolower(curchar);
    //while there's more alphanumeric characters, keep reading
    while(std::cin.get(curchar) && isalnum(curchar))
        curword += tolower(curchar);
    return curword.size();
}

int main() {
    std::unordered_set<std::string, std::vector<std::string>> anagrams;
    std::string curword;
    //for each word
    while(get_next_word(curword)) {
        std::vector<std::string>& anagram_set = anagrams[cannonical(curword)];
        //if it's not a duplicate
        bool duplicate = false;
        for(const std::string& compare : anagram_set) {
            if (compare == curword) {
                duplicate = true;
                break;
            }
        }
        //add it to the anagram set
        if (duplicate == false)
            anagram_set.push_back(std::move(curword));
    }
    for(const auto& pair : anagrams) {
        //for each anagram set
        std::vector<std::string>& anagram_set = pair.second;
        if (anagram_set.size() > 1) {
            //print them
            for(const std::string& word : anagram_set) 
                std::cout << word << ' ';
            std::cout << '\n';
        }
    }
}
