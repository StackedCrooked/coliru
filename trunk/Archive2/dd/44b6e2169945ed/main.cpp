#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    //                   0        3  4
    std::vector <int> v {1, 2, 3, 4, 6, 8, 9, 9, 10, 11, 12 };    
    // Znajdź pierwszą parę spełniającą predykat (następna większa o 2).
    auto it = std::adjacent_find (v.cbegin (), v.cend (), [] (int a, int b) {
        return b == a + 2;
    });
        
    std::cerr << std::distance (v.cbegin (), it) << std::endl;
    
    // I znów to samo, ale pomiń ten początek, wktórmyśmy już szukali.
    it = std::adjacent_find (it + 1, v.cend (), [] (int a, int b) {
        return b == a + 2;
    });

    std::cerr << std::distance (v.cbegin (), it) << std::endl;
}
