
#include <iostream>
#include <type_traits>

using namespace std;

template <typename T, const T &val> class TestClass
{
public:
  TestClass() : _val(val) { }
private:
  T _val;
};

extern constexpr float e = 2.72;
static constexpr float pi = 3.14;

int main()
{
  TestClass<float, e> test1;
  TestClass<float, pi> test2;
  cout << "Run..." << endl;
  return 0;
}
