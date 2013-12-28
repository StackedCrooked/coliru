#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

bool is_palindrome(std::string const& string) {
    std::vector<bool> table(string.size());
    std::transform(string.begin(), string.end(), string.rbegin(), table.begin(), std::equal_to<char>());
    return std::accumulate(table.begin(), table.end(), true, std::multiplies<bool>());
}

int main() {
    std::cout << is_palindrome("") << '\n';
    std::cout << is_palindrome("a") << '\n';
    std::cout << is_palindrome("abc") << '\n';
    std::cout << is_palindrome("abcba") << '\n';
}
