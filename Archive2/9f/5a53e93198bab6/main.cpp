#include <iostream>
#include <vector>
#include <algorithm>

int main()
{   //                       0
    std::vector <char> v1 { 'a', 'l', 'a', ' ', 'm', 'a', ' ', 
    //                                               12
                            'k', 'o', 't', 'a', ' ', 'a', 'l', 
                            'a', ' ', 'j', 'e', 's', 't', ' ', 
                            't', 'g', 'l', 'u', 'p', 'i', 'a' };
    
    std::vector <char> v2 {'a', 'l', 'a'};

    // Znajdź ostatnie wystąpienie "substringa" 'a','l','a' (12)
    auto it = std::find_end (v1.cbegin (), v1.cend (), v2.cbegin (), v2.cend ());
    std::cerr << std::distance (v1.cbegin (), it) << std::endl;
}
