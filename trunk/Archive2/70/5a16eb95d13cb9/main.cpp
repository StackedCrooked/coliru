#include <iostream>
#include <string>

using namespace std;

template <class T> class TempBase
{
protected:
  string m_str;
};

template <class T> class Temp: public TempBase<T>
{
public:
  void method()
  {
    string* ps3 = &(TempBase<T>::m_str); //this is workaround, works fine
    (*ps3) += "ciao";
    cout << *ps3 << endl;
  }
};

void f()
{
  Temp<int> t;
  t.method();
}

int main( int argc, char* argv[] ) 
{
    f();

}
