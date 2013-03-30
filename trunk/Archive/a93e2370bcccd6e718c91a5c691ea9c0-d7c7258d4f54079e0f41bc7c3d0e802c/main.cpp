#include <iostream>
#include <tuple>


#define TRACE std::cout << __PRETTY_FUNCTION__ << std::endl;


template<typename T, unsigned D, unsigned E>
struct Object
{    
    enum { Depth = D, MaxDepth = E };
    
    static T uniq() { static T t; return t++; }
    
    Object() : t(uniq())
    {
        std::cout << D << "/" << E << std::endl;
    }
    T t;
};


template<typename T, unsigned E>
struct Object<T, 0u, E>
{
    static T uniq() { static T t; return t++; }
    
    Object() : t(uniq())
    {
        std::cout << "Root at depth 0" << std::endl;
    }
    T t;
};



template<typename T, bool P, unsigned D, unsigned E>
struct Branch : Object<T, D, E>,
                Branch<T, false, D + 1u, E>,
                Branch<T, true,  D + 1u, E>
{
};


template<typename T, bool P, unsigned D>
struct Branch<T, P, D, D> {};


template<typename T, unsigned E>
using Root = Branch<T, false, 0u, E>;



template<typename T>
void check(const T &)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    std::cout << std::string(80, '=') << std::endl;
}

int main()
{
    check(Root<char, 1u>{});
    check(Root<char, 2u>{});
    check(Root<char, 3u>{});
    check(Root<char, 4u>{});
}