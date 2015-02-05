#include <boost/variant.hpp>
#include <iostream>

struct Circle {
    friend std::ostream& operator<<(std::ostream& os, Circle) {
        return os << "Circle";
    }
};

struct Rectangle {
    friend std::ostream& operator<<(std::ostream& os, Rectangle) {
        return os << "Rectangle";
    }
};

using Shape = boost::variant<Circle, Rectangle>;


int main() {

    Shape shape = Rectangle();
    std::cout << shape << "\n";

    shape = Circle();
    std::cout << shape << "\n";

}
