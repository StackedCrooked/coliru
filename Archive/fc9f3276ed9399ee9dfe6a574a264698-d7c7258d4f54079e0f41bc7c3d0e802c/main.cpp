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
        std::cout << "(" << D << " " << t << ") ";
    }
    T t;
};


template<typename T, unsigned E>
struct Object<T, 0u, E>
{
    static T uniq() { static T t; return t++; }
    
    Object() : t(uniq())
    {
        std::cout << "(" << 0 << " " << t << ") ";
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
struct Branch<T, P, D, D> : Object<T, D, D>
{
    Branch() { std::cout << "(STOP)"; }
};


template<typename T, unsigned E>
using Root = Branch<T, false, 0u, E>;



template<typename T>
void check(const T &)
{
    std::cout << "\n";
}

int main()
{
    check(Root<int, 0u>{});
    check(Root<int, 1u>{});
    check(Root<int, 2u>{});
    check(Root<int, 3u>{});;
}