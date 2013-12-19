#include <iostream>
using std::cout; using std::endl; using std::flush;
#include <string>
using std::string;

struct Foo {
  Foo() {cout << "Foo; " << flush;}
  Foo (const Foo& foo) {cout << "Foo copy; " << flush;}
  Foo (Foo&& foo) {cout << "Foo move; " << flush;}
  int size() {return 0;}
};

Foo foo1() {Foo tmp; return tmp;}
Foo foo2() {Foo tmp; const Foo& ref = tmp; return ref;}
Foo foo3() {Foo tmp; Foo& ref = tmp; return ref;}
Foo foo4() {Foo tmp; return (Foo&) tmp;}

int main() {
  cout << "foo1: " << flush; cout << foo1().size() << endl;
  cout << "foo2: " << flush; cout << foo2().size() << endl;
  cout << "foo3: " << flush; cout << foo3().size() << endl;
  cout << "foo4: " << flush; cout << foo4().size() << endl;
}
