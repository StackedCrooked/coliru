#include <iostream>
int main()
{
    const char* s = R"(°)";     // universal-character-name for the character '°' is \u00B0
    std::cout << s << '\n';
    const char* t = R"(\u00B0)";
    std::cout << t << '\n';
}
