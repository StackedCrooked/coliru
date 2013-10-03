#include <iostream>
#include <string>
#include <vector>

short square(short inputNum)
{
    return inputNum * inputNum;   
}

int main()
{
    std::cout << square(1000000L) << std::endl;
    return 0;
}
