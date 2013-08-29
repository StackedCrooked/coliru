#include <iostream>
#include <string>
#include <algorithm>


int main() {
    std::string s(u8"Grüezi mitenand");
    std::reverse(s.begin(), s.end());
    std::cout << s;
}

