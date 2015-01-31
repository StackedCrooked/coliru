#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main()
{
    std::vector<std::string> words;
    std::cout << "Enter words one by one. To stop, enter empty string.\n";
    std::string temp;
    while(std::getline(std::cin, temp) && temp != "")
        words.push_back(temp);
    std::sort(words.begin(), words.end());
    do {
        for(const auto& s: words)
            std::cout << s;
        std::cout << '\n';
    } while(std::next_permutation(words.begin(), words.end()));
}
