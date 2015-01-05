#include <iterator>
#include <vector>
#include <set>
#include <iostream>
#include <cstddef>

template <bool b, typename T = void>
struct enable_if {};

template <typename T>
struct enable_if<true, T> { typedef T type; };

template <typename T>
struct has_at
{
    typedef char (&yes)[1];
    typedef char (&no)[2];
    
    template <typename U, U u>
    struct SFINAE {};
    
    template <typename U>
    static yes test(SFINAE<typename U::reference(U::*)(std::size_t), &U::at>*);
    
    template <typename U>
    static no test(...);
    
    static const bool value = sizeof(test<T>(0)) == sizeof(yes);
};

template <typename Container>
typename enable_if<has_at<Container>::value>::type
    sorty(Container& container)
{
    std::cout << "O(N*lgN) complexity sorting\n";
}

template <typename Container>
typename enable_if<!has_at<Container>::value>::type
    sorty(Container& container)
{
    std::cout << "O(N*N) complexity sorting\n";
}

int main()
{
    std::vector<int> v;
    std::set<int> s;
    
    sorty(v);
    sorty(s);
}
