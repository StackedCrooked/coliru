#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <set>
#include <unordered_set>
#include <vector>
#include <type_traits>

template<int I> struct priority : priority<I - 1>{};
template<> struct priority<0>{};

class foo
{
public:
    int data;

    template<class It>
    bool in(It first, It last) const
    {
        std::cout << "iterator overload: ";
        return std::find(first, last, data) != last;
    }

    template<class T>
    bool in(std::initializer_list<T> il) const
    {
        std::cout << "initializer_list overload: ";
        return in(begin(il), end(il));
    }

    template<class Container>
    bool in(Container const& c) const 
    {
        std::cout << "container overload: ";
        return detail_in(priority<1>(), c);    
    }
    
private:
    template<class AssociativeContainer>
    auto detail_in(priority<1>, AssociativeContainer const& c) const 
    -> decltype(c.find(data), bool())
    {
        std::cout << "associative overload: ";
        return c.find(data) != end(c);    
    }

    template<class SequenceContainer> 
    bool detail_in(priority<0>, SequenceContainer const& c) const
    {
        std::cout << "sequence overload: ";
        return in(begin(c), end(c));    
    }
};

int main()
{
    foo f{1};
    std::cout << f.in({1, 2, 3}) << "\n";
    std::cout << f.in({2, 3, 4}) << "\n";

    int a1[] = { 1, 2, 3};
    int a2[] = { 2, 3, 4};

    std::cout << f.in(std::begin(a1), std::end(a1)) << "\n";
    std::cout << f.in(std::begin(a2), std::end(a2)) << "\n";

    std::cout << f.in(std::vector<int>{ 1, 2, 3 }) << "\n";
    std::cout << f.in(std::vector<int>{ 2, 3, 4 }) << "\n";

    std::cout << f.in(std::set<int>{ 1, 2, 3 }) << "\n";
    std::cout << f.in(std::set<int>{ 2, 3, 4 }) << "\n";
    
    std::cout << f.in(std::unordered_set<int>{ 1, 2, 3 }) << "\n";
    std::cout << f.in(std::unordered_set<int>{ 2, 3, 4 }) << "\n";    
}
