// User defined literals
// more here
// http://akrzemi1.wordpress.com/2012/08/12/user-defined-literals-part-i/

// Note on constexpr
// The constexpr specifier declares that it is possible to evaluate the value
// of the function or variable at compile time. Such variables and functions
// can then be used where only compile time constant expressions are allowed.
// constexpr implies const.

#include <iostream>

using namespace std;

// cooked literal
class Length
{
public:
  // like an ctor enum 
  class mmLength{};
  explicit Length(mmLength, double length)
    : m_length(length)
  {}
   
  void print() const
  {
    cout << "My length is " << m_length << "mm" << endl;  
  }
private:
  
  Length();
  
  double m_length;
  // in mm
};

Length operator"" _mm(long double mil)
{
  return Length(Length::mmLength(), static_cast<double>(mil));
}

Length operator"" _mm(unsigned long long mil)
// the integer version
{
  return Length(Length::mmLength(), static_cast<double>(mil));
}  

int main()
{
  Length l = 14.3_mm;
  l.print();
  
  l = 15_mm;
  l.print();
  
  return 0;
}