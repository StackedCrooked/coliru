#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::vector<int> a = {1, 2, 3, 4, 5};
    for(int v : a) std::cout << v << " ";
    return 0;
}
