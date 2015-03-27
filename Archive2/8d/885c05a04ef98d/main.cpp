#include <iostream>
#include <string>
#include <vector>

struct Test {
    operator int() {return 42;}
 };

int main()
{
    Test t;
    std::cout << t << std::endl;
}
