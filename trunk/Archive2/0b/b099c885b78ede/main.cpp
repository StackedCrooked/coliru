#ifndef BIRTHDAY_H
#define BIRTHDAY_H

#include <iostream>
#include <string>

class Birthday
{
public:
    Birthday(int y, int m, int d) : y(y), m(m), d(d) {}
    friend std::ostream& operator<<(std::ostream& os, const Birthday& bd);
private:
    int y, m, d;
};

#endif