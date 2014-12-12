#include <iostream>
#include <map>
#include <vector>

template <typename T>
struct tag {};

template <typename container>
class A
{
private:
    container m_container;    

    template <typename T, typename Alloc>
    void foo_spec(tag<std::vector<T, Alloc> >)
    {
        std::cout << "vector\n";
    }

    template <typename K, typename V, typename C, typename Alloc>
    void foo_spec(tag<std::map<K,V,C,Alloc> >)
    {
        std::cout << "map\n";
    }

public:
    void foo()
    {
        foo_spec(tag<container>());
    }

    // more generic methods that work with any container
};

int main()
{
    A<std::map<int,int> > a;
    A<std::vector<int> > b;
    a.foo();
    b.foo();
}
