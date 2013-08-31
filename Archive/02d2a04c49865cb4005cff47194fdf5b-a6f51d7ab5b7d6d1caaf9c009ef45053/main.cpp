#include <iostream>
#include <string>
#include <cctype>
 
long operator"" _lon (const char * str, std::size_t size)
{
    std::string accum;
    
    for(std::size_t i = 0; i < size; i++)
    {
        if(std::isdigit(str[i]))
        {
            accum+= str[i];
        }
    }
    return std::stol(accum, 0, 10);
}

int main()
{
 
    long x = "1,2,3,4,5"_lon;
    long y = "1_2_3_4_5"_lon;
    std::cout << x << std::endl << y;
 
}