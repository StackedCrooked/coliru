#include <iostream>
#include <string>


struct Point
{
    int x, y;
};


struct get_x
{
    friend int operator/(Point p, get_x)
    {
        return p.x;
    }
};


struct get_y
{
    friend int operator/(Point p, get_y)
    {
        return p.y;
    }
};



int main()
{
    Point point = { 3, 4};
    std::cout << '(' << point/get_x() << ',' << point/get_y() << ')' << std::endl;
}
