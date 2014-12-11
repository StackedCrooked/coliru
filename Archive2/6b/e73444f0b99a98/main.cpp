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
    std::vector <int> v1 { 7, 3, 8, 0, 4, 6, 5, 1, 2, 4 };
    std::vector <int>::iterator i = std::unique (v1.begin (), v1.end (), [] (int a, int b) { 
        return (a % 2) == (b % 2); 
    });
    
    v1.erase (i, v1.end ());    
    assert ((v1 == std::vector <int> { 7, 8, 5, 2 }));
}
