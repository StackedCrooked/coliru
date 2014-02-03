#include <iostream>
#include <vector>
#include <map>
#include <string>
 
int main()
{
    std::vector<std::string> stringvec = {"hello", "Alan"};
    
    for (auto it: stringvec)
    {
        std::cout << it << std::endl;
    }
}