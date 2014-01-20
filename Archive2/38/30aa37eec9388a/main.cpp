#include <iostream>
 
using namespace std;

class Set {
public:
  void foo();
  int bar;
};

void Set::foo() {
  bar = 999;
}

int main(){
  Set s;
  s.foo();
  cout << s.bar;
  return 0;
}