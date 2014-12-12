#include <iostream>
#include <type_traits>

template<typename T>
constexpr bool isInInterval3(T val, T LoEnd, T HiEnd)
{
    return val >= LoEnd && val <= HiEnd;
}

template <int A, typename Enable = void>
struct Check;

template <int A>
struct Check<A, typename std::enable_if<isInInterval3(A, 5, 10)>::type>
{
    void show() { std::cout << "5 - 10" << std::endl; }
};

template <int A>
struct Check<A,typename std::enable_if<isInInterval3(A, 11, 15)>::type>
{
    void show() { std::cout << "11 - 15" << std::endl; }
};

int main()
{
    Check<6> a;
    Check<11> b;
    
    a.show();
    b.show();
}