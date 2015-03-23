#include <iostream>
#include <vector>

int main(int argc, char* argv[])
{
    std::vector<int> v = {7,2,4};
    for (const int &x : v)
        std::cout << x << ' ';
    std::cout << std::endl;
    
    return 0;
}
