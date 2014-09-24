#include <iostream>
#include <vector>
 
int main() 
{
    std::vector<int> v = {10, 11, 12, 13, 14, 15};
    char *str ="venkatakrishnan";
    int count  = 0;
 
    for (int &i : v) // access by reference (const allowed)
        std::cout << i << ' ';
 
    std::cout << '\n';
 
    for (auto i : v) // compiler uses type inference to determine the right type
        std::cout << i << ' ';
 
    std::cout << '\n';
 
    for (int i : v) // access by value as well
        std::cout << i << ' ';
    
    for(; *str != 0 ; str++)
    {
        if(*str == 'a')
        count++;
    }
    
 
    std::cout << '\n'<<count;
}