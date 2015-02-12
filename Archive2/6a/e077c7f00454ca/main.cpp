#include <iostream>
#include <string>
#include <vector>



int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    for(std::string word : words)
        std::cout << word << std::endl;
}
