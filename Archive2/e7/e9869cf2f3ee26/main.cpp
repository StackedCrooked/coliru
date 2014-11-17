#include <iostream>
#include <vector>
#include <algorithm>

int main()
{   
    //                       0                                 9
    std::vector <int> v1 = { 2, 83, 0, 95, 54, 93, 83, 43, 13, 77, 50, 69, 62, 36, 58, 72, 83, 22, 69, 93 };
    std::vector <int> v2 = { 72, 75, 76, 77 };

    // Znajdź ostatnie wystąpienie "substringa" 'a','l','a' (12)
    auto it = std::find_first_of (v1.cbegin (), v1.cend (), v2.cbegin (), v2.cend ());
    std::cerr << std::distance (v1.cbegin (), it) << std::endl;
}
