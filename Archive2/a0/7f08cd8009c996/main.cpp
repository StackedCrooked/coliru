//#include "stdafx.h"
#include <vector>
#include <iostream>
#include <math.h>
using namespace std;

struct Points
{
        int x, y;

        Points(int paramx, int paramy) : x(paramx), y(paramy) {}

};//p1,p2;

vector <Points> pointes;

void addPoint(int a, int b);
void directionPoint(Points p1, Points p2);

int main()
{
    return 0;
}

void addPoint(int x, int y)
{
    pointes.push_back(Points(x, y));
}



void directionPoint(Points p1, Points p2)
{

    if ((p1.x*p2.y - p2.x*p1.y) > 0)
    {
        cout << "direction is anticlockwise" << endl;
    }
    else
        cout << "direction is clockwise" << endl;
}