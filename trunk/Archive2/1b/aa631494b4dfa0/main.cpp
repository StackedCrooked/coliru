#include <algorithm>
#include <vector>
#include <iostream>

bool func(int x, int y) {
    return (x-10)*(x-10) + (y-10)*(y-10) < 8*8;
}

int main()
{
    int rows = 40;
    int cols = 40;
    for (int y=0; y<rows; y++) {
      for (int x=0; x<cols; x++) {
        if (func(x, y)) {
            std::cout << "#";
        } else {
            std::cout << " ";
        }
      }
      std::cout << "\n";
    }
    std::cout << "\n";
    return 0;
}



