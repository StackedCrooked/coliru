#include <iostream>
#include <algorithm>

int main() {
    int input[][5] = { { 13, 27, 4 , 1 , 11 },
                        { 11, 19, 2 , 37, 1  },
                        { 32, 64, 11, 22, 41 },
                        { 71, 13, 27, -8, -2 },
                        { 0 , -9, 11, 99, 13 } };
                        
    std::sort(&input[0][0], &input[4][5]);
    
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            std::cout << input[i][j] << ' ';
}