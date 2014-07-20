#include <iostream>
#include <string>

int countWords(std::string x);

int main() {
    std::cout << countWords("Hello world!") << std::endl;
    std::cout << countWords("") << std::endl;
    std::cout << countWords(" ") << std::endl;
    std::cout << countWords("  Hello   World!  ") << std::endl;
    std::cout << countWords("I") << std::endl;
}

int countWords(std::string x) {

    int Num = 0;      
    char prev = ' ';

    for(unsigned int i = 0; i < x.size(); i++) {

        if(x[i] != ' ' && prev == ' ') Num++;
       
        prev = x[i];
    }
    return Num;
}

