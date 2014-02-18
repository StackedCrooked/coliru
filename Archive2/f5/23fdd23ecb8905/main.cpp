#include <map>
#include <algorithm>
#include <iostream>
#include <cassert>

int main()
{
    typedef std::map<char, int> M;
    
    M m;
    m['a'] = 5;
    m['b'] = 8;
    m['c'] = 2;
    
    M::const_iterator it = std::max_element(
        std::begin(m), std::end(m),
        [](M::value_type& lhs, M::value_type& rhs) { return lhs.second < rhs.second; }
    );
    
    assert(it != m.end());
    std::cout << it->first << '\n';  // 'b'
}