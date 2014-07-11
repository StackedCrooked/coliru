#include <algorithm>
#include <array>
#include <initializer_list>
#include <type_traits>
#include <iostream>
#include <set>
#include <unordered_set>
#include <vector>

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
        return detail_in(c, associative_container_tag{});    
    }
    
private:
    struct sequence_container_tag {};
    struct associative_container_tag: sequence_container_tag {};

    template<class AssociativeContainer>
    auto detail_in(AssociativeContainer const& c, associative_container_tag) const 
    -> decltype(c.find(data), bool())
    {
        std::cout << "associative overload: ";
        return c.find(data) != end(c);    
    }

    template<class SequenceContainer> 
    bool detail_in(SequenceContainer const& c, sequence_container_tag) const
    {
        std::cout << "sequence overload: ";
        using std::begin; using std::end;
        return in(begin(c), end(c));    
    }
};

int main()
{
    foo f{1};
    int a1[] = { 1, 2, 3};
    int a2[] = { 2, 3, 4};

    std::cout << f.in({1, 2, 3}) << "\n";
    std::cout << f.in({2, 3, 4}) << "\n";

    std::cout << f.in(std::begin(a1), std::end(a1)) << "\n";
    std::cout << f.in(std::begin(a2), std::end(a2)) << "\n";

    std::cout << f.in(a1) << "\n";
    std::cout << f.in(a2) << "\n";

    std::cout << f.in(std::array<int, 3>{ 1, 2, 3 }) << "\n";
    std::cout << f.in(std::array<int, 3>{ 2, 3, 4 }) << "\n";

    std::cout << f.in(std::vector<int>{ 1, 2, 3 }) << "\n";
    std::cout << f.in(std::vector<int>{ 2, 3, 4 }) << "\n";

    std::cout << f.in(std::set<int>{ 1, 2, 3 }) << "\n";
    std::cout << f.in(std::set<int>{ 2, 3, 4 }) << "\n";
    
    std::cout << f.in(std::unordered_set<int>{ 1, 2, 3 }) << "\n";
    std::cout << f.in(std::unordered_set<int>{ 2, 3, 4 }) << "\n";    
}
