#include <iostream>

class Point
{  
public:
    int X, Y;

    int dis()
    {
        std::cout << X << Y << std::endl;
        return X;
    }

    int operator=(const Point&)
    { 
        int dat = 3;
        return dat;
    }
};

int main()
{ 
    Point p2 = Point();
    p2.dis();
    return 0;
}