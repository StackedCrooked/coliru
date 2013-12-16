#include <algorithm>
#include <iostream>
#include <initializer_list>
const std::size_t n = 5;

class array
{
public:
    int A[n];
    array(std::initializer_list<int> il) : A{}
    {
        std::copy(il.begin(), il.begin() + std::min(n, il.size()), A);
    }
private:
    int x;
};

int main()
{
    array a = {1,2,3};
    std::cout << "The array contents are: ";
    for(int n: a.A)
        std::cout << n << ' ';
}
