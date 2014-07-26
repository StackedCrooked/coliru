#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

template <typename T>
class Outer
{
  private:
  struct Inner
  {
    T val;
    Inner (T v) : val(v) { }
  };

  public:
  Inner* ptr = nullptr;

  friend class Other;
};

template <typename T>
void testFunction (const typename Outer<T>::Inner* p)
{
  cout << p->val << endl;
}

template<>
class Outer<double>{
    public:
  struct Inner
  {
    double val;
    Inner (double v) : val(v) { }
  };

  Inner* ptr = nullptr;
};
int main()
{
    
    Outer<double>::Inner i(1.0);
    testFunction<double>(&i);
    return 0;
}
