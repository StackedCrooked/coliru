#include <chrono>
#include <iostream>
int main()
{
    if(std::chrono::seconds(2) == std::chrono::milliseconds(2000))
        std::cout <<  "2 s == 2000 ms\n";
    else
        std::cout <<  "2 s != 2000 ms\n";
 
    if(std::chrono::seconds(61) > std::chrono::minutes(1))
        std::cout <<  "61 s > 1 min\n";
    else
        std::cout <<  "61 s <= 1 min\n";
 
}