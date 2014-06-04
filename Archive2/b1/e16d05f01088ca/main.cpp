#include <string>
#include <iostream>

int main() {
    std::string sentence;
    std::getline(std::cin, sentence);
    
    unsigned int count[26] = {0}; // number of letters in the alphabet
    
    for (unsigned int i = 0; i < sentence.length(); ++i) {
        if (std::isalpha(sentence[i]) && std::islower(sentence[i]))
            ++count[sentence[i] - 'a'];
    }
    
    for (char c = 0; c < 26; ++c) {
        if (count[c] != 0)
            std::cout << static_cast<char>(c + 'a') << ": " << count[c] << '\n';
    }
        
    return 0;
}