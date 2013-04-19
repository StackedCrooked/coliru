#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
class MyClass
{
public:
    void run(int val){}
};
struct f{
  int val;
  f(int val) : val(val) {}
  void operator()(MyClass& x) {
     x.run(val);
  }
};
int main()
{
 std::vector<MyClass> v(10);
 int val = 5;
 std::for_each(v.begin(), v.end(), f(val));

    std::cout << "End \n";
}
