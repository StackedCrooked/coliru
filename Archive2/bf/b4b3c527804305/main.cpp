#include <array>
#include <iostream>
#include <vector>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/comparison.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/logical.hpp>

using namespace boost;

// in C++98, use 
// template<int R, int C>
// struct is_runtime_sized: mpl::if<
// ...
// >::type {};
template<int R, int C>
using is_runtime_sized = typename mpl::if_<
    mpl::or_<
        mpl::equal_to<mpl::int_<R>, mpl::int_<0>>,
        mpl::equal_to<mpl::int_<C>, mpl::int_<0>>
    >,
    mpl::true_, mpl::false_
>::type;

template<class T, int R, int C, bool = is_runtime_sized<R, C>::value>
struct MatrixStorage
{
    MatrixStorage() = default;
    MatrixStorage(int r, int c): data_(r * c) {} // zero-initializes
protected:    
    std::vector<T> data_;
};

template<class T, int R, int C>
struct MatrixStorage<T, R, C, false>
{
    MatrixStorage() = default;
    MatrixStorage(int, int): data_{} {} // zero-initializes
protected:    
    std::array<T, R * C> data_;    
};

template<class T, int R = 0, int C = 0>
struct Matrix: public MatrixStorage<T, R, C>
{
    Matrix() = default;
    using MatrixStorage<T, R, C>::MatrixStorage;
    int size() const { return this->data_.size(); }
};

int main()
{
    Matrix<int> m_dyn(3, 3);
    std::cout << m_dyn.size() << "\n"; // 9
    
    Matrix<int, 2, 2> m_stat;
    std::cout << m_stat.size() << "\n"; // 4
}
