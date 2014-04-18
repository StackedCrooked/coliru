#include <iostream>

class Rectangle {
public:
    Rectangle() {}
    
    int width, height;
};

int main() {
    Rectangle r;
    
    std::cout << "w: " << r.width << "; h: " << r.height << std::endl;

    return 0;
}