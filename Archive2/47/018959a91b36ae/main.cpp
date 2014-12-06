#include <vector>
#include <iostream>

template <typename T>
T& declval();

struct A
{
    A(std::vector<int> const&) {std::cout << __PRETTY_FUNCTION__ << '\n';}
    A(std::vector<int>&&) = delete;
};

void f(A);

int main()
{
    f(declval<std::vector<int> const>());
    
    f(std::vector<int>() );
}
