#include <iostream>


// FIND THE ERRORS
struct Point
{
    Point(int x, int y) : x(new int(x)), y(new int(y)) {}

    ~Point() {
        delete x;
        delete y;
    }

    int * x;
    int * y;
};

// HINT
void print(Point p)
{
    std::cout << *p.x << ", " << *p.y << std::endl;
}

int main()
{
    Point p(3, 4);
    print(p);
    print(p); // prints different result!?
}