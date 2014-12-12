#include <iostream>
#include <map>
#include <vector>

template <typename T>
struct Impl;

template <typename T, typename A>
struct Impl<std::vector<T, A> >
{
    static void foo_spec()
    {
        std::cout << "vector\n";
    }
};
    
template <typename K, typename V, typename C, typename A>
struct Impl<std::map<K,V,C,A> >
{
    static void foo_spec()
    {
        std::cout << "map\n";
    }
};

template <typename container>
class A
{
private:
    container m_container;
    
public:
    void foo()
    {
        Impl<container>::foo_spec();
    }
};

int main()
{
    A<std::map<int,int> > a;
    A<std::vector<int> > b;
    a.foo();
    b.foo();
}
