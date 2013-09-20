#include <iostream>
using namespace std;
class Point {
  int x, y;
public:
  Point() {}
  Point(int px, int py) 
  {x = px;y = py;}
  void show() {
    cout << x << " ";
    cout << y << "\n";
  }
  Point operator+(Point op2);
  Point operator,(Point op2);
};

// overload comma for Point
Point Point::operator,(Point op2)
{
  Point temp;
  temp.x = op2.x;
  temp.y = op2.y;
  cout << op2.x << " " << op2.y << "\n";
  return temp;
}

// Overload + for Point
Point Point::operator+(Point op2)
{
  Point temp;
  temp.x = op2.x + x;
  temp.y = op2.y + y;
  return temp;
}

int main()
{
  Point ob1(10, 20), ob2( 5, 30), ob3(1, 1);
  Point ob4;
  ob1 = (ob1, ob2+ob2, ob3);//Why control is not reaching comma operator for ob1?
  ob1 = (ob3, ob2+ob2, ob1);//Why control is not reaching comma operator for ob3?
  ob4 = (ob3+ob2, ob1+ob3);//Why control is not reaching comma operator for ob3+ob2?
  return 0;
}