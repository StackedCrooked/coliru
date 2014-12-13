#include <vector>
class Foo{};
class Foo1{
  std::vector<Foo> vec;
public:
  void foo(){
    Foo obj;
    vec.push_back(obj);
  }
};
int main(){
  Foo1 obj;
  obj.foo();
  return 0;
}