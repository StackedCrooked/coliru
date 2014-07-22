#include <iostream>
#include <string>

int main() {
    std::string text = R"(\
This is the second line.
This is the third line.
)";
    std::cout << "Test:" << text;
}
