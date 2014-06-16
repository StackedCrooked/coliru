#include <iostream>
#include <vector>

int main() {
    const std::size_t n = 4;
    
    {
        std::vector<double> hack;
        hack.push_back(5);
        hack.push_back(6);
        hack.push_back(7);
        hack.push_back(8);
        hack.push_back(9);
        hack.push_back(10);
        hack.push_back(11);
        hack.push_back(12);
    }
    
    double* a = new double [n];
    double* b = new double [n]();
    
    for (std::size_t i = 0; i < n; i++)
        std::cout << a[i] << '/' << b[i] << ' ';
    std::cout << '\n';
    
    delete[] a;
    delete[] b;
}