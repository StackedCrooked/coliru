#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    
    for(auto &s: words) {
        std::cout << s << std::endl;
    }
}
