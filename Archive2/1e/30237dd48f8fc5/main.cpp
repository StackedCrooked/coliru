#include <iostream>
#include <cctype>
#include <algorithm>
#include <string>

void crypto(std::string& s)
{
    std::cout << "Before: " << s << std::endl;
    std::transform(s.begin(), s.end(), s.begin(),
                   [](char c) {
                    if(std::isalpha(static_cast<unsigned char>(c))) {
                        if(std::islower(static_cast<unsigned char>(c))) {
                            return static_cast<char>('z' - (c - 'a'));
                        } else {
                            return static_cast<char>('Z' - (c - 'A'));
                        }
                    }
                    return c;
                   });
    std::cout << "After:  " << s << std::endl;
}

int main()
{
    std::string s = "ABCdef123";
    crypto(s);
}
