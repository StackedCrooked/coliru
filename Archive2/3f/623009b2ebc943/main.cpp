#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    //                             E  O  O  E
    std::vector <int> v1 {1, 2, 3, 4, 5, 3, 6, 7, 8, 9 };
    
    // Even, odd
    enum Parity { E, O };
    std::vector <Parity> v2 {E, O, O, E};
    
    // Wyszukaj w v1 początek ciągu liczb, gdzie pierwsza 
    // jest parzysta, potem 2 niep. a potem znów parzysta:
    auto it = std::search (v1.cbegin (), v1.cend (), v2.cbegin (), v2.cend (), [] (int a, Parity b) { 
        if (b == E) {
            return a % 2 == 0;
        }
        
        return a % 2 == 1;
    });
        
    std::cerr << std::distance (v1.cbegin (), it) << std::endl;
}
