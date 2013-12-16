#include <iostream>

class point {
  typedef void (point::*bool_type)() const;
  void not_supported() const{} // should have body too!

public:
  double x, y;
  bool real;
  point(double x_, double y_): x(x_), y(y_), real(true) {}
  point(): x(0), y(0), real(true) {}

  operator bool_type() 
  {
    return (real == true)? &point::not_supported : 0;
  }
  
  bool operator==(point const & p) const { return x == p.x && y == p.y; }
  bool operator!=(point const & p) const { return !(*this == p); }
};

class test {};

class another_test 
{
  typedef void (another_test::*bool_type)() const;
  public:
     operator bool_type() 
     {
       return 0;
     }
};

int main()
{
    point p1{},p2{};
    
#if 1  //use 0 to disable this block and enable #else block  
    p1==p2;   //ok
    p1!=p2;   //ok
#else    
    test t{};
    another_test at{};
    p1 != t;   //error
    p1 == t;   //error
    p1 == at;  //error
    p1 != at;  //error
#endif

}