#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>

bool foo(char c) {
    return !std::isalnum(c) && !std::isspace(c);
}

int main() {
    std::string variable1("Hello, world!");

    variable1.erase(
        std::remove_if(
            variable1.begin(),
            variable1.end(),
            &foo
        ),
        variable1.end()
    );

    std::cout << variable1 << '\n';

    return 0;
}
