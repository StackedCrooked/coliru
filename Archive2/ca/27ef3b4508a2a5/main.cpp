#include <iostream>
#include <iomanip>

#include <vector>
#include <algorithm>

#include <random>
#include <cctype>
#include <chrono>

// unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count();

std::random_device rd; 
auto seed1= rd();

std::minstd_rand0 g1 (seed1);
std::uniform_int_distribution<int> dist(32, 126);

char get_random_char() {
    return (char)dist(g1);
}

template <class Pred>
std::string generate_string(int length, Pred pred) {
    int index = 0;
    std::string final = "";
    while (true) {
        char current = get_random_char();
        if (!pred(index, current)) continue;

        final += current;

        index++;
        if (index >= length) break;
    }
    return final;
}
    
int main(int argc, char* argv[]) {
    std::cout << std::left << std::setw(10) << "Word";
    std::cout << " Sanity check" << std::endl;
        
    for (int j = 0; j < 10; j++) {
        std::string test = generate_string(10, [&] (int i, char c) {
                if (i == 0 && isdigit(c)) return false;
                if (ispunct(c) && c != '_') return false;
                if (isspace(c)) return false;
                return true;
        });
        std::cout << std::left << std::setw(10) << test;
        std::cout << " ";
        std::cout << "Contains space? " << std::boolalpha << 
                        !(test.find(" ") == std::string::npos);
        std::cout << " ";
        std::cout << "First character is digit? " <<
                        (isdigit(test[0]));
        std::cout << std::endl;
    }

    return 0;
}