#ifndef BIRTHDAY_H
#define BIRTHDAY_H

#include <iostream>

class Birthday
{
public:
    Birthday(int y, int m, int d) : y(y), m(m), d(d) {}
    friend std::ostream& operator<<(std::ostream& os, const Birthday& bd)
    {
        return os << bd.m << '/' <<bd.d << '/' << bd.y;
    }
private:
    int y, m, d;
};

#endif