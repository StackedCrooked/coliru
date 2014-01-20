#include <iostream>
#include <string>
#include <vector>

void print(std::vector<std::string> words, int spaces = 0) {
    for(int i = 0; i < spaces; i++)
        std::cout << ' ';
    std::cout << words[words.size()-1];
    words.pop_back();
    if(!words.empty()) {
        std::cout << std::endl;
        print(words, spaces+1);
    }        
}

int main()
{
    std::vector<std::string> words;
    words.push_back("Hoi");
    words.push_back("Hoi");
    words.push_back("Hoi");
    words.push_back("Hoi");
    words.push_back("Hoi");
    words.push_back("Hoi");
    std::cout << "Start" << std::endl;
    print(words);
}
