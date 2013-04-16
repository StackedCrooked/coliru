#include <iostream>
#include <unordered_map>
#include <string>

using S = std::string;


// Write a function f(a, b) which takes two character string arguments and
// returns a string containing only the characters found in both strings in the
// order of a.
// Write a version which is order N-squared and one which is order N.

// O(n) solution
S f(S a, S b)
{
    std::unordered_map<char, bool> m;
    for (auto c : b) m[c] = true;
    
    // retain order
    std::string result;
    for (auto c : a) if (m.count(c)) result += c;
    return result;
}

int main()
{
    std::cout << f("abcdef", "foobar") << std::endl;
}