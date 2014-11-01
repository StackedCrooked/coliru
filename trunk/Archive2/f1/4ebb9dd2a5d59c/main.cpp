#include <iostream>
#include <cmath>
#include <memory>
#include <string>
#include <vector>

using namespace std::literals;

const double Pi = atan2(0, -1);

class Shape
{
public:
    virtual double area() = 0;
    virtual std::string name() = 0;
    virtual ~Shape() = default;
};

class Rectangle: public Shape
{
public:
    Rectangle(double x_, double y_) : x(x_), y(y_) {}
    virtual double area() {return x*y;};
    bool is_square() {return x == y;}
    virtual std::string name() {return is_square() ? "Square"s : "Rectangle"s;}
private:
    double x;
    double y;
};

class Ellipse: public Shape
{
public:
    Ellipse(double x_, double y_) : r1(x_), r2(y_) {}
    virtual double area() {return r1*r2*Pi;}
    bool is_circle() {return r1 == r2;}
    virtual std::string name() {return is_circle() ? "Circle"s : "Ellipse"s;};
private:
    double r1;
    double r2;
};

std::unique_ptr<Shape> create_rectangle(double x, double y)
{
    return std::make_unique<Rectangle>(x, y);
}

std::unique_ptr<Shape> create_square(double side)
{
    return std::make_unique<Rectangle>(side, side);
}

std::unique_ptr<Shape> create_ellipse(double x, double y)
{
    return std::make_unique<Ellipse>(x, y);
}

std::unique_ptr<Shape> create_circle(double r)
{
    return std::make_unique<Ellipse>(r, r);
}

int main()
{
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(create_rectangle(20, 10));
    shapes.push_back(create_square(15));
    shapes.push_back(create_ellipse(12, 14));
    shapes.push_back(create_circle(10));
    auto end = shapes.size();
    for(decltype(end) i = 0; i < end; ++i)
        std::cout << "Shape " << i << " is a " << shapes[i]->name() <<
                     " and its area is " << shapes[i]->area() << '\n';
}