#include <iostream>
#include <string>
#include <cctype>
using std::string;
using std::isalpha;

bool isAlphabetic(string s)
{
    static std::size_t i = 0;
    if (i==s.size())
    {
        i = 0;
        return true;
    }
    else if (!isalpha(s[i])){
        return false;
    }
    i++;
    return isAlphabetic(s);
}

int main()
{
    std::cout << isAlphabetic("123");
    std::cout << isAlphabetic("abc");
    std::cout << isAlphabetic("1bc");
    std::cout << isAlphabetic("b1c");
    std::cout << isAlphabetic("def");
}
