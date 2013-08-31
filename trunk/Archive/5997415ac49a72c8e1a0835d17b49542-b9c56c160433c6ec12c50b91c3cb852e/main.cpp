#include <functional>
#include <utility>
 

struct foo
{
  template <typename... Args>
  void invoke(int n, Args&&... args) {
    auto x = [&,this](int i){ bar(i,(args)...); }; 
    //...
  }
  
  template <typename... Args>
  void bar(int, Args&&...)
  { }
};

 
int main() {
foo f;
f.invoke(1, 2);
}