#include <iostream>
#include <array>

void print(const std::array<std::array<int, 5>, 3>& matrix)
{
    std::cout << "Matrix : \n";
    for(int i = 0; i < 3; ++i)
    {
        for(int j = 0; j < 5; ++j)
            std::cout << matrix[i][j] << " " ;
        std::cout << std::endl ;
    }
}

int main()
{
    std::array<std::array<int, 5>, 3> matrix ;
    for(int i = 0; i < 3; ++i)
        for(int j = 0; j < 5; ++j)
            matrix[i][j] = j - i ;
            
    print(matrix);
    
    for(int i = 0; i < 3; ++i)
        for(int j = 0; j < i; ++j)
            if(matrix[j][4] > matrix[i][4])
                std::swap(matrix[i], matrix[j]);
                
    print(matrix);
    
}