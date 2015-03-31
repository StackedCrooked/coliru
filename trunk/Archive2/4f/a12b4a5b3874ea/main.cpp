#include <iostream>

int main()
{
    unsigned val1 = 5;
    unsigned val2 = val1 - 1;
    unsigned difference = val2 - val1;
    std::cout << "val1 was modified by '" << difference << "'\n";
}
