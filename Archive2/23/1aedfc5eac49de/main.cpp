#include <iostream>
#include <string>

class A {
public:
    A(const std::u16string& s) {  }
};

int main() {
  std::u16string s = u"boo";
  new A(s);
}