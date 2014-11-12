#include <map>
#include <iostream>
#include <cctype>

int main() {
    std::map<char, unsigned int> letterCount;

    char ch;
    while (std::cin >> ch && ch != '.') {
        if (std::isspace(ch)) continue;
        ++letterCount[ch];
    }

    std::cout << "ch\tcount\n";
    for (const auto& it : letterCount)
        std::cout << it.first << '\t' << it.second << '\n';

    return 0;
}