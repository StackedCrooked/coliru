#include <iostream>
 
using namespace std;
 
class point {
public:
   // ctors
   // having default values is redudant with: point(): x(0), y(0) { } 
   point(double X=0.0, double Y=0.0): x(X), y(Y)  { }
   // accessors
   double getx() const { return x; }
   double gety() const { return y; }
   // mutators
   void setx(double v) { x=v; }
   void sety(double v) { y=v; }
 
   point operator+(const point& p1) {
      return { p1.getx() + x, p1.gety() + y};                           // compiles only in c++11
   }
 
// declare operator<< as a friend to have full access to the class 
// friend ostream& operator<<(ostream& out, const point& p);
 
private:
   double x, y;
};
 
// operationi+ overload definition ouside class point
//point operator+(const point& p1, const point& p2) {
//   // point sum=point(p1.getx() + p2.getx(), p1.gety() + p2.gety());    // non c++11
//   point sum= { p1.getx() + p2.getx(), p1.gety() + p2.gety()};          // compiles only in c++11
//   return sum;
//}
 
// if declared as friend you could access p.x and p.y directly!
ostream& operator<<(ostream& out, const point& p) {
   out << "(" << p.getx() << "," << p.gety() << ")";
   return out;
}
 
 
int main() {
   // point a(3.5,2.5), b(2.5, 4.5), c;                                 // non c++11
   point a{3.5,2.5}, b{2.5, 4.5}, c;                                    // compiles only in c+11
 
   cout << "a= " << a << " b= " << b << endl;
   cout << "c (ctor init) = " << c << endl;
   cout << "sum (a+b) = " << a+b << endl;
 
   return 0;
}