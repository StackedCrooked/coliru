#include <iostream>
#include <string>

int main()
{
    unsigned char array[6] = { 'f','o','o','b','a','r' };
    std::string name;
    
    for (auto i : {1,0,0,3,4,5})
        name += array[i];
    
    std::cout << name << '\n';
}
