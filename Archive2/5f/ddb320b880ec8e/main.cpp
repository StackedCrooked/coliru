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
    
    template <typename T, typename A>
    void foo_spec(tag<std::vector<T, A> >)
    {
        std::cout << "vector\n";
    }
    
    template <typename K, typename V, typename C, typename A>
    void foo_spec(tag<std::map<K,V,C,A> >)
    {
        std::cout << "map\n";
    }
    
public:
    void foo()
    {
        foo_spec(tag<container>());
    }
};

int main()
{
    A<std::map<int,int> > a;
    A<std::vector<int> > b;
    a.foo();
    b.foo();
}
