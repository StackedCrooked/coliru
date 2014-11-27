#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <cassert>
#include <iterator>
#include <cstdlib>

int main()
{
    std::vector <int> v (10);
    std::iota (v.begin (), v.end (), 0);
    assert ((v == std::vector <int> {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}));
    
    std::array <char, 10> a;
    a.back () = '\0';
    std::iota (a.rbegin () + 1, a.rend (), 97);
    std::cerr << a.data () << std::endl;
}
