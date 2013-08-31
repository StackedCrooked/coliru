#include <iostream>
#include <string>
#include <vector>

bool is_palindrome(std::string input)
{
    if (input.size() < 2) return true;
    if (input.size() == 2) return input.front() == input.back();
    return input.front() == input.back() && is_palindrome(std::string(input.begin() + 1, input.end() - 1)); // hope I got that right`
}

int main()
{
    std::cout << is_palindrome("");
    std::cout << is_palindrome("a");
    std::cout << is_palindrome("aa");
    std::cout << is_palindrome("ab");
    std::cout << is_palindrome("aba");
    std::cout << is_palindrome("abc");
}
