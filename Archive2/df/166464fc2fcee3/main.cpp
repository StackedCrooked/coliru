#include <fstream>
#include <iostream>
#include <string>
#include <map>


template<typename T, T...>
struct Enum
{
    
};


int main()
{
    Enum<int, 1, 2, 3> en;
}