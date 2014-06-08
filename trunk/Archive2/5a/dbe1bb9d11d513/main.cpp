#include <iostream>
#include <string>

void func(std::string str)  {
    str[1] = '@';
    std::cout << str << '\n';
    std::cout << str.size() << '\n';
}

int main() {
    char temp[] = "pinta";
    func(temp);
}
