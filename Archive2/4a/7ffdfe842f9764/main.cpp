#include <iostream>

void f(const int i)
{
    switch (i) {
        case 3: {
            static int x = 0;
            std::cout << x;
            x = 3;
            std::cout << x << ' ';
            break;
        }
        
        case 4: {
            static int x = 0;
            std::cout << x;
            x = 4;
            std::cout << x << ' ';
            break;
        }
    }
}

int main()
{
    f(3);
    f(4);
}