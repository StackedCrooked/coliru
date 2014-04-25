#include <iostream>

int main()
{
    std::cout << static_cast<char*>(nullptr);
    bool has_badbit = std::cout.bad();

    std::cout.clear();
    std::cout << std::boolalpha << "bad(): " << has_badbit << std::endl;
}
