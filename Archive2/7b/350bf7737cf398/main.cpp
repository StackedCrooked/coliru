#include <iostream>
#include <vector>

int main()
{
    std::vector<int> v1{1, 2, 3, 4};
    std::cout << v1.data() << '\n';
    std::vector<int> v2{std::move(v1)};
    std::cout << v2.data() << '\n';
}
