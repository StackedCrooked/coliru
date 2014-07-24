#include <string>
#include <vector>
#include <algorithm>

#include <iostream>
#include <sstream>

int main(int argc, char** argv) {
    if(argc != 3) return 17;

    std::vector<std::string> args(argv, argv+argc);

    std::vector<std::string> words;
    std::string word;
    while(std::cin >> word) { words.emplace_back(std::move(word)); }
    
    if(args[1] == "e") {
        std::stringstream ss(args[2]);
        int hash;
        ss >> std::hex >> hash;
        auto hi = (hash / words.size());
        auto lo = (hash % words.size());
        std::cout << words[hi] << ' ' << words[lo] << '\n';
    } else if(args[1] == "d") {
        std::stringstream ss(args[2]);
        std::string hi_word, lo_word;
        ss >> std::hex >> hi_word >> std::hex >> lo_word;
        int hi = std::find(words.begin(), words.end(), hi_word) - words.begin();
        int lo = std::find(words.begin(), words.end(), lo_word) - words.begin();
        std::cout << std::hex << (hi * words.size() + lo) << '\n';
    } else return 17;
}
