#include <list>
#include <iostream>
#include <cassert>

using std::list;

std::ostream& operator<<(std::ostream& os, const list<char>& l)
{
    os << '{';
    for (auto el : l)
        os << el << ',';
    os << '}';
    
    return os;
}

int main()
{
    list<char> l{'a', 'b', 'c'};
    list<char>::iterator insertAt { std::next(std::begin(l)) }; // 'b'
    
    std::cout << l << '\n';
    
    list<char>::iterator newEl { l.insert(insertAt, 'd') };
    
    std::cout << l << '\n';
    
    assert(std::distance(std::begin(l), insertAt) == 2);
    assert(std::distance(std::begin(l), newEl)    == 1);
}