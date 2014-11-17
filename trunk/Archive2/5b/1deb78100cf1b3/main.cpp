#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::vector <int> v {1, 2, 3, 4, 4, 4, 5, 6, 7, 8, 9, 9, 9};    

    // Znajdź mi 3 dziewiątki pod rząd:
    std::cerr << std::distance (v.begin (), std::search_n (v.begin (), v.end (), 3, 9)) << std::endl;
    
    // Znajdź mi 3 parzyste liczby pod rząd! Uwaga! Predykat przyjmuje 2 argumenty!
    std::cerr << std::distance (v.begin (), std::search_n (v.begin (), v.end (), 3, 0, [] (int element, int value) { return element % 2 == 0; })) << std::endl;
}
