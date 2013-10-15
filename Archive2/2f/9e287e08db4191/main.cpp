#include <iostream>
#include <string>
#include <vector>

#include "square.h"


int main()
{
    Square sq(3);
    float area = sq.getArea();
    cout << "area: " << area << endl;
}
