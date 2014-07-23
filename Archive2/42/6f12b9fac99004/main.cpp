#include <iostream>
#include <string>



int main() {
        std::string text = 1+R"(
This is the first line.
This is the second line.
This is the third line.
)";

    std::cout << "Text{\n" << text << "}";
}
