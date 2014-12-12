#include <iostream>
#include <map>
#include <vector>

template <typename container>
class A;

template <typename CRTP>
struct Base;

template <typename T, typename Alloc>
struct Base<A<std::vector<T, Alloc> > >
{
    void foo()
    {
        A<std::vector<T, Alloc> >* that = static_cast<A<std::vector<T, Alloc> >*>(this);
        std::cout << "vector\n";
    }
};
    
template <typename K, typename V, typename C, typename Alloc>
struct Base<A<std::map<K,V,C,Alloc> > >
{
    void foo()
    {
        A<std::map<K,V,C,Alloc> >* that = static_cast<A<std::map<K,V,C,Alloc> >*>(this);
        std::cout << "map\n";
    }
};

template <typename container>
class A : public Base<A<container> >
{
private:
    container m_container;
    friend class Base<A<container> >;
};

int main()
{
    A<std::map<int,int> > a;
    A<std::vector<int> > b;
    a.foo();
    b.foo();
}
