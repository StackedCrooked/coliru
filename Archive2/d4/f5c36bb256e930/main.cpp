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
    std::vector <int> v1 { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    auto it = std::remove_if (v1.begin (), v1.end (), [] (int i) { return i % 2 == 0; });
    // Fizyczna liczba elementów nie zmienia się     | <- tu jest logiczny koniec
    assert ((v1 == std::vector <int> { 1, 3, 5, 7, 9, 6, 7, 8, 9 }));
    
    // A tu jest przycięta
    v1.erase (it, v1.end ());
    assert ((v1 == std::vector <int> { 1, 3, 5, 7, 9 }));
}
