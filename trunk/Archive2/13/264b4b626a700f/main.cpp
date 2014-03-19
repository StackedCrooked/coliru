#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << __func__ << __VERSION__ << std::endl;
}
