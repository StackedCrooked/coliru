#include <iostream>
#include <type_traits>

template < typename T >
struct Matrix
{
    void multiply()
    {
        std::cout << "non-specialized" << std::endl;
    }
};

template <>
void Matrix<float>::multiply()
{
    std::cout << "specialized for float" << std::endl;
}

int main()
{
    Matrix<int>{}.multiply();
    Matrix<float>{}.multiply();
}

