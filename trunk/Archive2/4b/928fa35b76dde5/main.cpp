#include <string>
#include <iostream>

int main()
{
    std::string s = "abababababababa";
    while (!s.empty()) {
        char c = s[0];
        s.erase(std::remove(s.begin(), s.end(), c), s.end());
        std::cout << s << std::endl;
    }
    return 0;
}