#include <iostream>

namespace matrix_operators
{
    struct tag {};
    template <typename T>
    T operator+ (T lhs, T const& rhs) {
        lhs += rhs;
        return lhs;
    }
}

template<size_t N, size_t M>
class matrix
    : matrix_operators::tag
{
public:
    matrix<N, M>& operator+= (matrix<N, M> const&) {
        std::cout << "matrix<" << N << ", " << M << "::operator+=()\n";
        return *this;
    }
};

template<size_t N>
class vector:
    public matrix<N,1>
{
public:
    /*vector<N>& operator+= (vector<N> const& other) {
        matrix<N, 1>::operator+= (other);
        return *this;
    }*/
    void some_other_method() {
        std::cout << "vector<" << N << ">::some_other_method()\n";
    }
};

int main()
{
    vector<3> a, b;
    (a + b).some_other_method();
}