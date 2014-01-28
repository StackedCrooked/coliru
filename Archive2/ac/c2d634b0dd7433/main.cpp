#include <iostream>

class Shape {
public:
    Shape& operator=(const Shape&) =delete;
    Shape(Shape&&) =delete; //no move operations
    Shape& operator=(Shape&&) =delete;
    ~Shape();
protected:
    Shape(const Shape&) = default;
    Shape() = default;
    
};

class Circle: public Shape
{
    public:
    Circle(int i) : a(i) {}
    Circle* clone() const { return new Circle(*this); }
    int a;
};

int main()
{
    Circle* p = new Circle(1);
    std::cout << p->a << std::endl;
}

