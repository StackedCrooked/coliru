#include <iostream>
#include <cmath>

const size_t HEIGHT = 15;
const size_t WIDTH  = 64;
const size_t REPEAT = 2;

const double PI     = 3.14159;

int main()
{
    for (size_t y = 0; y < HEIGHT; y++) {
        for (size_t x = 0; x < WIDTH*REPEAT; x++) {
            const float val_at_x = sin((x/(float)WIDTH) * 2 * PI);
            if ((unsigned int)round((HEIGHT/2) + val_at_x*(HEIGHT/2)) == HEIGHT-y-1)
                std::cout << '*';
            else
                std::cout << ' ';
        }
        
        std::cout << '\n';
    }
}