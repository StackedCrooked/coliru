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
    std::vector <int> v1 { 7, 2, 2, 2, 5, 4, 4, 5, 6 };
    std::vector <int>::iterator i = std::unique (v1.begin (), v1.end ());
    v1.erase (i, v1.end ());    
    assert ((v1 == std::vector <int> { 7, 2, 5, 4, 5, 6 }));
}
