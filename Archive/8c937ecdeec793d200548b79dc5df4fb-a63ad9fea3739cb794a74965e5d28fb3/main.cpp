#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

int main()
{
    std::vector<std::string> v1;
    for_each(begin(v1), end(v1), [](std::string s1) {
        std::vector<std::string> v2;
        for_each(begin(v2), end(v2), [](std::string s2) {
            std::cout << "...";
        });
    });
}