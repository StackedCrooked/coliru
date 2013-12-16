#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main(int, char*[]) {
    std::vector<std::string> vect;
    vect.emplace_back("sled");
    vect.emplace_back("car");
    vect.emplace_back("house");
    vect.emplace_back("dog");
    
    if (std::all_of(
        vect.begin() + 1,
        vect.end(),
        [&](const std::string& s) {
            return s == vect.front();
        }
    )) {
        std::cout << "They are all equal!";
    } else {
        std::cout << "Not equal";
    }
    return 0;
}