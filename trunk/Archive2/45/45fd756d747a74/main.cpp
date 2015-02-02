#include <iostream>

class Shape {
public:
    virtual int area() const = 0;
    // note no virtual destructor, an obvious bug for an abstract class
};

class Rect: public Shape {
    int width, height;
    
    // this method is private in Rect and cannot be called 
    // (yes, you can override public methods with private ones in C++)
    virtual int area() const { // it should have an `override` specifier, since it's C++11 anyways
        return width * height;
    }
    
public:
    Rect(int width, int height): width(width), height(height) {}
};



int main() { 
    Rect r{ 3, 4 };
    
    // error: 'virtual int Rect::area() const' is private
    std::cout << r.area() << std::endl;
    
    // if you want it to get called, you can call it like this:
    std::cout << static_cast<Shape&>(r).area() << std::endl;
    
}
