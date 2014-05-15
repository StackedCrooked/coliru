#include <string>
#include <iostream>
#include <regex>
int main() {
    std::string s = "123 apples 456 oranges 789 bananas oranges bananas";
    std::regex r("[a-z]+");

    for(std::sregex_iterator i = std::sregex_iterator(s.begin(), s.end(), r);
                            i != std::sregex_iterator();
                            ++i )
    {
        std::smatch m = *i;
        std::cout << m.str() << " at position " << m.position() << '\n';
    }
}
