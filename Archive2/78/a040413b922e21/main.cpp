
#include <iostream>
#include <algorithm>
#include <vector>
 
int main() {
    // Supprimer les nombres hors d'un intervalle
 
    std::vector<int> nombres = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int min = 3;
    int max = 6;
 
    nombres.erase(std::remove_if(nombres.begin(), nombres.end(), [&] (int nombre) {
        return nombre < min || nombre > max;
    }), nombres.end()); 

    for (auto n: nombres)
        std::cout << n << " ";
    std::cout << std::endl;
}