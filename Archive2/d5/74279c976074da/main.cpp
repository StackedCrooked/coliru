#include <iostream>
using std::cout;
using std::endl;

enum MyEnum2 {A=0,B=1};

class Test{
public:
 operator MyEnum2 () { return val_;} 
 Test(MyEnum2 val) :val_(val) {}
 Test() {}
 static const MyEnum2 A;
 static const MyEnum2 B;
 MyEnum2 val_;
 };

const MyEnum2 Test::A(MyEnum2::A);
const MyEnum2 Test::B(MyEnum2::B);

static const Test ll;

int main() {
  class Test v = ll.A;
  cout << v << endl;
  switch(v) {
    case ll.A:
    cout << "A" << endl;
    break;

    case ll.B:
    cout << "B" << endl;
    break;
  }
}
