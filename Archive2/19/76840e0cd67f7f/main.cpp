#include <cstdlib>
#include <iostream>

class Rectangle{
public:
    Rectangle(double l=0.0, double w =0.0) : length(l), width(w){}
    double getLength() {return length;}
    double getWidth() { return width;}
    //virtual double Area() { return length * height;}
protected:
    double length, width;
};
class Box : public Rectangle {
public:
    Box(double l, double w, double h) : Rectangle(l, w), height(h){}

    double getHeight() {return height;}
    double Volume();
    double Area(){
        return 6*length * width;
    }
private:
    double height;
};

int main() {
}