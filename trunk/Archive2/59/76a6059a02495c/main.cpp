#include <string>
#include <iostream>
#include <algorithm>

int main()
{
    std::string s = "abababababababa";
    while (!s.empty()) {
        char c = s[0];
        s.erase(std::remove_if(s.begin(), s.end(), c), s.end());
        std::cout << s << std::endl;
    }
    return 0;
}