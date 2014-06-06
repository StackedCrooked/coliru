#include <iostream>
#include <string>
#include <vector>

int main() {
    long testCaseCount = 0;
    std::cin >> testCaseCount;
    std::vector<std::string> testCases(testCaseCount);
    for (auto& s : testCases)
        std::cin >> s;
    for (const auto& s : testCases)
        std::cout << s << '\n';
}