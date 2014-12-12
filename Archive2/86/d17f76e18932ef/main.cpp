#include <iostream>
#include <valarray>

int main()
{
    std::valarray<std::valarray<double>> A(std::valarray<double>(6), 2);
    std::valarray<double> B{ 1, 4, 9 };
    A[0][std::slice(0,B.size(),2)] = B;
    A[1][std::slice(1,B.size(),2)] = B;
    
    for (auto& v : A)
    {
        for (auto& e : v)
        {
            std::cout << e << "\t";
        }
        std::cout << std::endl;
    }
}
