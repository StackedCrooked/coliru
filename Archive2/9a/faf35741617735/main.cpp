#include <iostream>

class Boolean {
public:
    virtual operator bool() const = 0;
};

class Number {
public:
    virtual operator float() const = 0;
};

struct Axis : Number { operator float() const {return 0.f;} };

int main()
{
    Axis a;
    float f = a;
}