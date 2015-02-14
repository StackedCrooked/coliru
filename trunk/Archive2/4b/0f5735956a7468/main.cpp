#include <string>
#include <iostream>
#include <sstream>
using namespace std;

class WrapSStream
{
public:
  template <typename T>
  WrapSStream& operator<<(const T& val)
  {
    ss << val;
    return *this;
  }

  operator string(){return ss.str();}
  
  stringstream ss;
};

struct Base {
    string msg;
    Base(const string& msg) : msg(msg) { }
};

struct Derived: public Base {
    Derived(int value)
    // Parent constructor requires a string so we have to create it inline
      : Base(WrapSStream() << "This is class " << value)
    { }
};

int main(void)
{
    int i = 5; // some number obtained at runtime
    Derived d(i);
    cout << d.msg << "\n";
    return 0;
}
