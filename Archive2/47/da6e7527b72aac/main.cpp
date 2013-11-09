#include <iostream>
#include <type_traits>

namespace matrix_operators
{
    struct tag {};
    
    template <typename T>
    T operator+ (T const& lhs, T const& rhs) {
        return T(lhs) += rhs;
    }
    
    // enable_if because `T` might be an lvalue, and therefore deduced as lvalue ref
    // alternatively, use a non-deduced context:
    // T&& lhs, typename std::remove_reference<T>::type const& rhs
    // (obvious drawback: allows conversions for rhs)
    template <typename T, class U, class = typename std::enable_if<std::is_same<typename std::decay<T>::type, U>{}>::type>
    T operator+= (T&& lhs, U const& rhs) {
        lhs.operator+=(rhs);
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
    (a+=b).some_other_method();
}