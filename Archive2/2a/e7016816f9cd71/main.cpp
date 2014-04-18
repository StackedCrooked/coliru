#include <iostream>

class RectangleA {
public:
    RectangleA(int x, int y) : width{x}, height{y} {}
    
    int width, height;
};

class RectangleB {
public:
    RectangleB(int x, int y) {
        width  = x;
        height = y;
    }
    
    int width, height;
};

int main() {
    RectangleA a{1,2};
    RectangleB b{3,4};
    
    std::cout << "Area of a: " << a.width * a.height << std::endl;
    std::cout << "Area of b: " << b.width * b.height << std::endl;

    return 0;
}