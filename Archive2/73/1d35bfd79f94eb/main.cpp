#include <iostream>
#include <map>
#include <vector>

template <typename container>
class Base
{
private:    
    container m_container;
    
public:
    // more generic methods that work with any container
};

template <typename container>
class A;

template <typename T, typename Alloc>
class A<std::vector<T, Alloc> > : public Base<std::vector<T, Alloc> >
{
public:
    void foo()
    {
        std::cout << "vector\n";
    }
};
    
template <typename K, typename V, typename C, typename Alloc>
class A<std::map<K,V,C,Alloc> > : public Base<std::map<K,V,C,Alloc> >
{
public:
    void foo()
    {
        std::cout << "map\n";
    }
};

int main()
{
    A<std::map<int,int> > a;
    A<std::vector<int> > b;
    a.foo();
    b.foo();
}
