#include <iostream>
#include <tuple>


#define TRACE std::cout << __PRETTY_FUNCTION__ << std::endl;


template<typename T, bool B, unsigned I, unsigned D>
struct Object
{    
    enum { Index = I, Depth = D };
    
    static T uniq() { static T t; return t++; }
    
    Object() : t(uniq())
    {
        std::cout << static_cast<int>(B) << ' ' << I << std::endl;
    }
    T t;
};


template<typename T, unsigned D>
struct Object<T, false, 0u, D>
{
    static T uniq() { static T t; return t++; }
    
    Object() : t(uniq())
    {
        std::cout << static_cast<int>(false) << ' ' << 0u << std::endl;
    }
    T t;
};



template<typename T, bool P, unsigned I, unsigned D>
struct Branch : Object<T, P, I, D>,
                Branch<T, false, I + 1u, D>,
                Branch<T, true,  I + 1u, D>
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