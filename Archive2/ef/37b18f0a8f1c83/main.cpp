#include <map>
#include <iostream>
int main()
{
    std::map<int, std::map<int, int>> map =
    {
        { 1, { { 1, 0 }, { 2, 1 } } },
        { 2, { { 1, 1 }, { 2, 0 } } },
    };
    std::cout << "WorksForMe\n";
} 
