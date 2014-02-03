#include <iostream>

/*struct foo
{
    template <typename T>
    using pauli = hermitian_matrix<T, 2>;
    
    template <typename T>
    constexpr pauli<T> sigma1 = { { 0, 1 }, { 1, 0 } };
};*/

template <typename T>
T pi = T{3.14};

template <typename T>
struct foo
{
    template <typename T>
    T pi = T{3.14};
};

int main()
{

}
