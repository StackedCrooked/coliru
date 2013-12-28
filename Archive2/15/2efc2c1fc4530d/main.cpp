#include <algorithm>
#include <cassert>
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
    assert(is_palindrome(""));
    assert(is_palindrome("a"));
    assert(!is_palindrome("abc"));
    assert(is_palindrome("abcba"));
}
