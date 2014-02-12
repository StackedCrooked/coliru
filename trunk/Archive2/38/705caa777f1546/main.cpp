#include <array>
#include <iostream>
#include <typeinfo>
using namespace std;


template <typename T, size_t I, size_t... J>
struct matrix {
    using nested = typename matrix<T, J...>::type;
    using type = array<nested, I>;
};

template <typename T, size_t I>
struct matrix<T, I> {
    using type = array<T, I>;
};

template <typename T, size_t I, size_t... J>
using Matrix = typename matrix<T, I, J...>::type;

int main()
{   
    Matrix<int, 3, 3, 3, 3> x;
    cout << typeid(x).name() << endl;
}