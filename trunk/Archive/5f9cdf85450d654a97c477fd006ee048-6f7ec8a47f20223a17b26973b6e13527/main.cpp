#include <vector>
#include <iostream>

int main()
{
    std::vector<std::vector<int>> a(10, std::vector<int>(6));
    
    for(int h = 0; h < 10; h++)
    {
        for(int w = 0; w < 6; w++)
        {
                a[h][w] = h + w;
        }
    }
    
    for( auto const& w: a ) {
        for( auto const& h: w ) {
            std::cout << h << ", ";
        }
        std::cout << '\n';
    }
    
    std::vector<std::vector<int>> b;
    
    b = a;
    
    for( auto const& w: b ) {
        for( auto const& h: w ) {
            std::cout << h << ", ";
        }
        std::cout << '\n';
    }
}
