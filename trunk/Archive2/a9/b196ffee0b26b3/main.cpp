#include <iostream>

class Shape {
public:

    Shape(int x, int y) {
        this->x = x;
        this->y = y;
    }
    
    virtual ~Shape() {}
    
    virtual void area() = 0;
    
    bool positive(int, int) {
        return true;
    }
    
private:

    int x;
    int y;
    
};

class Square : public Shape {
public:

    Square(int x, int y) : Shape(x, y) {}

    virtual void area() {
        std::cout << "Temp" << std::endl;
    }
    
};

int main() {
    Square sq(1, 1);
    sq.area();
}