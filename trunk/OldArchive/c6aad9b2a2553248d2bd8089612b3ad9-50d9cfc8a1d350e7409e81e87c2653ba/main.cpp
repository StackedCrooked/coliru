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
  void operator()(MyClass& x, int val) {
     x.run(val);
  }
};
int main()
{
 std::vector<MyClass> v(10);
 int val = 5;
 std::for_each(v.begin(), v.end(), f());

    std::cout << "End \n";
}
