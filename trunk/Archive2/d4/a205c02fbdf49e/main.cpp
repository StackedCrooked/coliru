#include <iostream>
#include <string>

int main() {
    char arr[] ="ab\0c";
    std::string s(arr, arr + 4);
    std::cout << s.size() << '\n' << s << '\n' << s.c_str();
}
