//incandadd.cpp
#include <iostream>

using namespace std;

struct Point
{
    int x;
    int y;
};


 int inc_and_add (Point &p)
 {
    ++p.x;
 	++p.y;

 	return p.x + p.y;
 }

int main ()
{
	Point p = {3, 2};
	cout << inc_and_add(p) << endl;
	cout << p.x << " " << p.y << endl;
	return 0;
}