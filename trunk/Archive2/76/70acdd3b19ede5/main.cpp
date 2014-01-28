#include <iostream>

class Shape {
public:
    Shape(const Shape&) = delete;
    Shape& operator=(const Shape&) =delete;
    Shape(Shape&&) =delete; //no move operations
    Shape& operator=(Shape&&) =delete;
    virtual ~Shape() = default;
protected:
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
    Circle a(1);
    Circle* p = a.clone();
    std::cout << a.a << "  " << p->a << '\n';
}

