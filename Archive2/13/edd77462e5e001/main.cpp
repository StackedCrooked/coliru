#include <iostream>

void swap(int & x, int & y) {
    int tmp = x; x = y; y = tmp;
}

int main()
{
    int x = 5;
    int y = 10;
    std::cout << "x:" << x << ", y:" << y << "\n";
    
    swap(x, y);
    
    std::cout << "x:" << x << ", y:" << y;
}
