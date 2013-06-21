#include <iostream>
#include <vector>

int main()
{
    std::vector<int> v {1,2,3,4,5};
    std::cout << v.capacity() << '\n';
    std::vector<int>().swap(v);
    std::cout << v.capacity();
}
