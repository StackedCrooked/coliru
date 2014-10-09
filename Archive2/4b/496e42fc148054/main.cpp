#include <iostream>
#include <string>
#include <vector>

int main ()
{
    
    std::vector<std::vector<std::string>> vec 
    {
        3, { "abc", "cde", "fgh", "ijk" }
    };

    for (v : vec) {
        for (s : v)
            std::cout << s << ",";
        std::cout << "\n";
    }
}