#include <iostream>

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

  friend struct Other;
};

template <typename T>
void testFunction (const typename Outer<T>::Inner* p)
{
  cout << p->val << endl;
}

struct Other {
  template<typename T>
  static void main(const Outer<T>& foo)
  {
    testFunction<T>(foo.ptr);  //this line is flagged as the error
  }
};

int main()
{
    Outer<double> o;
    Other::main(o);
    return 0;
}
