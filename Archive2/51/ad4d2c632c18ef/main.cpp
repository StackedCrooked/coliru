struct Point {
    Point() {}
    Point(int x, int y): x_(x), y_(y) {}
    int x_, y_;
};

union U {
    int z;
    double w;
    Point p = Point(1,2);
};


#include <iostream>
int main () {
    U u;
    std::cout << u.p.x_ << ":" << u.p.y_ << std::endl;
}
