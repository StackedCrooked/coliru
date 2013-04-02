#include <iostream>
#include <cstdint>

void myfunc(std::int32_t something)
{
    std::cout << "int32_t" << std::endl;
}

void myfunc(std::int16_t something)
{
    std::cout << "int16_t" << std::endl;
}

int main()
{
    std::int32_t myint = 5;
    myfunc(myint);

    return 0;
}
