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
    std::vector <int> v1 (6);
    std::vector <int> v2 (6);
    std::iota (v1.begin (), v1.end (), 0);

    // Z v1 do v2, ale każdą 2 zamień na 22.
    std::replace_copy (v1.cbegin (), v1.cend (), v2.begin (), 2, 22);
    assert ((v2 == std::vector <int> {0, 1, 22, 3, 4, 5}));
    
    // Z v2 do v1, ale każdą nieparzystą zamień na 666
    std::replace_copy_if (v2.cbegin (), v2.cend (), v1.begin (), std::bind (std::modulus <int> (), std::placeholders::_1, 2), 666);
    assert ((v1 == std::vector <int> {0, 666, 22, 666, 4, 666}));
}
