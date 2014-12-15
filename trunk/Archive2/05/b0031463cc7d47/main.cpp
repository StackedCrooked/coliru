#include <vector>
#include <iostream>
 

int main()
{
    std::vector<int> v1;
    int sz = 10000;
    v1.reserve(sz);
    for(int n = 0; n < sz; ++n)
            v1[n] = n;
    for (int n = 0; n < sz; ++n)
        std::cout << v1[n] << std::endl;
}