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
        auto hi = (hash / 235886);
        auto lo = (hash % 235886);
        std::cout << words[hi] << ' ' << words[lo] << '\n';
    } else if(args[1] == "d") {
        std::stringstream ss(args[2]);
        std::string hi_word, lo_word;
        ss >> std::hex >> hi_word >> std::hex >> lo_word;
        int hi = std::find(words.begin(), words.end(), hi_word) - words.begin();
        int lo = std::find(words.begin(), words.end(), lo_word) - words.begin();
        std::cout << std::hex << (hi * 235886 + lo) << '\n';
    } else return 17;
}
