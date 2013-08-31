#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
class MyClass
{
public:
    void run(){}
};
struct f{
  void operator()(MyClass& x) {
     x.run();
  }
};
int main()
{
 std::vector<MyClass> v(10);
 
 std::for_each(v.begin(), v.end(), f());

    std::cout << "End \n";
}
