#include <iostream>

//make function factory and use it
#define FUNCTION(name, a) int fun_##name() { return a;}

FUNCTION(abcd, 12)
FUNCTION(fff, 2)
FUNCTION(kkk, 23)

#undef FUNCTION
#define FUNCTION 34
#define OUTPUT(a) std::cout << #a << std::endl;

int main()
{
    std::cout << "abcd: " << fun_abcd() << std::endl;
    std::cout << "fff: " << fun_fff() << std::endl;
    std::cout << "kkk: " << fun_kkk() << std::endl;
    std::cout << FUNCTION << std::endl;
    OUTPUT(million);               //note the lack of quotes
}