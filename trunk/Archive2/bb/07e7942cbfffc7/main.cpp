#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct StringWrap {};

template<typename T>
struct PeekDeque {
    PeekDeque(int) {}    
};

void testNewWord(const std::string &, std::vector<PeekDeque<StringWrap> > &chains) {
    chains.push_back(PeekDeque<StringWrap>(100));
}

int main(int argc, char **argv){   
    if(argc != 2){
        std::cerr << "Please specify a SINGLE .txt file to process.\n";
        return 1;
    }

    std::vector<PeekDeque<StringWrap> > chains;
    std::ifstream inFile(std::string(argv[1]).c_str());

    std::string word;
    while (inFile >> word) {
        std::cout << word << '\n';
        testNewWord(word, chains);
    }
}
