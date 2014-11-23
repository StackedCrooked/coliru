//incandadd.cpp
#include <iostream>

using namespace std;

struct Point
{
int x;
int y;
};

 int inc_and_add (struct Point p)
 {

     int &x = ++p.x;
 	int &y = ++p.y;


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