#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>

const std::string hangman[] = {
R"(
    +---+
    |   |
        |
        |
        |
        |
        |
  ============
)",
R"(
    +---+
    |   |
    O   |
        |
        |
        |
        |
  ============
)",
R"(
    +---+
    |   |
    O   |
    |   |
        |
        |
        |
  ============
)",
R"(
    +---+
    |   |
    O   |
   /|   |
        |
        |
        |
  ============
)",
R"(
    +---+
    |   |
    O   |
   /|\  |
        |
        |
        |
  ============
)",
R"(
    +---+
    |   |
    O   |
   /|\  |
   /    |
        |
        |
  ============
)",
R"(
    +---+
    |   |
    O   |
   /|\  |
   / \  |
        |
        |
  ============
)"
};

void printfooter(const std::string& status) {
    for(auto& i : status) {
        std::cout << i << "  ";
    }
}

void printguesses(const std::vector<char>& guesses) {
    std::cout << "\n\nGuessed: ";
    if(guesses.empty()) {
        std::cout << "Nothing!";
        return;
    }
    for(auto& i : guesses)
        std::cout << i << "  ";
}

bool changeStatus(const std::string& original, std::string& status, char input) {
    if(original.find(input) == std::string::npos)
        return false;
    size_t pos = original.find_first_of(input);
    status[pos] = original[pos];
    for(size_t i = pos+1; i < original.size(); ++i) {
        if(original[i] == input)
            status[i] = original[i];
    }
    return true;
}

int main() {
    std::srand(std::time(0));
    size_t life = 0;
    char input;
    std::ifstream file("words.txt"); 
    std::vector<std::string> words;
    std::vector<char> guesses;
    std::copy(std::istream_iterator<std::string>(file),std::istream_iterator<std::string>(),std::back_inserter(words));
    std::string original = words[std::rand() % words.size()];
    std::string status = original;
    for(auto& i : status) i = '_';

    while(true) {
        std::cout << hangman[life];
        printfooter(status);
        printguesses(guesses);
        std::cout << "\n\nEnter a guess: ";
        std::cin >> input;
        guesses.push_back(input);
        if(!changeStatus(original,status,input))
            ++life;
        if(life == 7) {
            std::cout << "\nYou have lost...\nThe word was: " << original << '\n';
            break; 
        }
        if(status == original) {
            std::cout << "\n~~~You won!~~~\nThe word was: " << original << '\n';
            break;
        }
    }
}