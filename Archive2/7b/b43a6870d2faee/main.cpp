#include <iostream>
#include <string>
#include <cctype>
#include <set>

const std::string SECRET("Mississipi");

int main() {
    
    std::string guess(SECRET.length(), '_');
    std::set<char> used;
    int guessed = SECRET.length();
    char v;
    while (guessed > 0) {
        std::cout << "Enter your guess: ";
        std::cin >> v;
        for (int l = 0; l < SECRET.length(); l++) {
            if (tolower(SECRET[l]) == tolower(v)) {
                if (guess[l] == '_') {
                    guess[l] = v;
                    guessed--;
                }
                else break;
            }
        }
        used.insert(v);
        std::cout << guess << std::endl << "Used characters:\n";
        for (auto k : used)
            std::cout << k << ' ';
        std::cout << std::endl;
    }
    
    std::cout << "You guessed it!\nThe secret word is: " << SECRET << std::endl;
}