/* File: Examples\derived.cpp
   derived classes
*/
#include <iostream>
#include <stdlib.h>
using namespace std;

class CPolygon {
  protected:
    int width, height;
  /* members of a derived class can access the protected members
     inherited from the base class, but not its private members
  */
  public:
    void set_values (int a, int b)
      { width=a; height=b;}
};

class CRectangle: public CPolygon { // CRectangle derived from CPolygon
// all members that are public in CPolygon will be public in CRectangle
  public:
    int area ()
      { return (width * height); }
};

class CTriangle: public CPolygon {
  public:
    int area ()
      { return (width * height / 2); }
};

int main() {
  CRectangle rect;        // contains members inherited from CPolygon:
  CTriangle  trgl;        // width, height, set_values()
  rect.set_values (4,5);
  trgl.set_values (4,5);
  cout << rect.area() << endl;
  cout << trgl.area() << endl;

  return 0;
}
