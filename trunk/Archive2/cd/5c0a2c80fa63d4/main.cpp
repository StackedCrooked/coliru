#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::vector<std::vector<std::string>> allInput;
    std::vector<std::string> input1;
    std::vector<std::string> input2;
    input1.push_back("ABC");
    input2.push_back("DEF");
    allInput.push_back(input1);
    std::cout << "Hello world\n";
}