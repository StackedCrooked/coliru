#include <iostream>
#include <string>



int main() {
        std::string text =
"\
This is the first line." R"(
This is the second line.
This is the third line.)";

    std::cout << "Text{" << text << "}";
}
