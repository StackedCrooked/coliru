#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::vector <int> v1 { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    // Czy wszystkie są mniejsze niż 10? TAK!
    std::cerr << std::all_of (v1.cbegin (), v1.cend (), [] (int i) { return i < 10; }) << std::endl;
    
    // Czy jest jakikolwiek parzysty? TAK!
    std::cerr << std::any_of (v1.cbegin (), v1.cend (), [] (int i) { return i % 2 == 0; }) << std::endl;
    
    // Żadny ma niespełniać warunku i < 0. 
    std::cerr << std::none_of (v1.cbegin (), v1.cend (), [] (int i) { return i < 0; }) << std::endl;
}
