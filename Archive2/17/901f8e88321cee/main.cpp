#include <iostream>
#include <cmath>

const int HEIGHT = 16;
const int WIDTH  = 64;
const int REPEAT = 2;

const double PI  = 3.14159;

int main()
{
    for (int y = HEIGHT/2; y >= -HEIGHT/2; y--) {
        for (size_t x = 0; x < WIDTH*REPEAT; x++) {
            const float val_at_x = sin((x/(float)WIDTH) * 2*PI);
            if ((int)round(val_at_x*HEIGHT/2) == y)
                std::cout << '*';
            else
                std::cout << ' ';
        }
        
        std::cout << '\n';
    }
}