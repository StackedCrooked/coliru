struct Shape {};
struct Point { int x, y; };

struct Circle : Shape {
    Point center;
    int radius;
    
    Circle(Point c, int r) : center(c), radius(r) {}
};

struct Smiley : Circle {
    using Circle::Circle;
};

#include <iostream>
int main() {
    Smiley happy{ Point{ 300, 200 }, 100 };
    
    std::cout << happy.center.x << ' ' << happy.center.y << ' ' << happy.radius << '\n';
}
