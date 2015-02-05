#include <boost/variant.hpp>
#include <iostream>

struct Point { double x,y; };

struct Circle {
    
    Point centre;
    double radius;

    friend std::ostream& operator<<(std::ostream& os, Circle) {
        return os << "Circle";
    }
};

struct Rectangle {
    Point topleft, bottomright;

    friend std::ostream& operator<<(std::ostream& os, Rectangle) {
        return os << "Rectangle";
    }
};

struct area_f : boost::static_visitor<double> {
    double operator()(Rectangle const& r) const {
        return std::abs(r.bottomright.x - r.topleft.x) * 
               std::abs(r.bottomright.y - r.topleft.y);
    }
    double operator()(Circle const& r) const {
        return (r.radius*r.radius) * M_PI;
    }
};

using Shape = boost::variant<Circle, Rectangle>;

double area(Shape const& s) {
    return boost::apply_visitor(area_f(), s);
}

int main() {

    Shape shape = Rectangle { { 1,1 }, { 5,5 } };
    std::cout << shape << ": " << area(shape) << "\n";

    shape = Circle { { 10, 10 },  5 };
    std::cout << shape << ": " << area(shape) << "\n";

}

