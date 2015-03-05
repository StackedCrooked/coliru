#include <iostream>

struct Point
{
    int x, y;
};

int main()
{
    int Height = 3;
    Point pt = { Height, Height };
    Point pts[] = { { Height, Height }, { Height, Height }, { Height, Height } };
    return 0;
}