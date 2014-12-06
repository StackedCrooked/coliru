#include <vector>
#include <iostream>

template <typename T>
T& declval();

struct B
{
    B(std::vector<int>);
};

struct A
{
    template <typename T> A(T&) {std::cout << __PRETTY_FUNCTION__ << '\n';}
    
private:

    A(B);
};

void f(A);

int main()
{
    f( declval<std::vector<int> const>() );
    
    f(std::vector<int>()); // Error
}
