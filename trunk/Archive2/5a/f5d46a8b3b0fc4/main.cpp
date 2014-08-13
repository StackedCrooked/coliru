#include <iostream>
#include <string>

int main()
{
for (auto i = 1; i < 101; ++i)
    std::cout << (i%3 ? i%5 ? std::to_string(i) : "Pop" : (std::string("Crackle") + (i%5 ? "" : "Pop"))) << std::endl;
}
