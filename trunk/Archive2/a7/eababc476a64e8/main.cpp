#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

int main()
{
    std::vector <int> v1 { 1, 2, 3, 4, 5, 6 };
    std::vector <int> v2 { 1, 2, 3, 6, 5, 6 };
    
    // Zwróci 1.
    std::cerr << std::is_sorted (v1.cbegin (), v1.cend ()) << std::endl;
    
    // Wypisze 5 - oczywiście zazwyczaj należy  sprawdzić, czy nie end
    std::cerr << *std::is_sorted_until (v2.cbegin (), v2.cend ()) << std::endl;
}
