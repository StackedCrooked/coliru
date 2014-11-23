//incandadd.cpp
#include <iostream>

using namespace std;

struct Point
{
int x;
int y;
};
struct Point p;

 int inc_and_add (int x, int y)
 {
     ++x;
 	++y;

 	int sum = x+y;

 	return sum;
 }

int main ()
{
	Point p = {3, 2};
	cout << inc_and_add(p) << endl;
	cout << p.x << " " << p.y << endl;
	return 0;
}