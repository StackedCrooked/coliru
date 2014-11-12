#include <iostream>

int main() {
    int n;
    
    std::cin >> n;
    
    char *array = new char[n];
    
    for (auto x : array) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
    
    delete[] array;
}
