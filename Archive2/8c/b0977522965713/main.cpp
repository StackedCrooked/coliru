#include <iostream>
#include <string>
#include <vector>


std::vector<double> make_vector()
{
    return {3, 1.2};
}

int main()
{
    std::vector<double> vec = make_vector();
    
    for (auto i : vec)
    {
        std::cout << i << std::endl;
    }
}
