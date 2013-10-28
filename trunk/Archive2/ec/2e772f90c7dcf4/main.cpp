#include <string>
#include <algorithm>
#include <iostream>

int main()
{
    std::string variable1 = "a%%%%%";
    variable1.erase(
        std::remove_if(
            variable1.begin(),
            variable1.end(),
            [] (char c) { return !std::isalnum(c) && !std::isspace(c); }
        )
    );
    std::cout << variable1;
}