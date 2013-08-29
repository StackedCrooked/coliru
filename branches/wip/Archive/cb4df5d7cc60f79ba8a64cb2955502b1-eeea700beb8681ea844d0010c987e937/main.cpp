#include <iostream>

using namespace std;

struct B {
  int i;

  // this prevents the definition of an implicit default constructor
  B( int j ) : i(j) {}

};

struct C {
  int i;

  // i is not mentioned in the initializer list
  // the compiler will call default constructor for i
  C() {}

};


int main() {

  int x( 1 );
  cout << " x = " << x << endl;

  // error: no matching function for call to ‘B::B()’
  //B b4 = B();
  //cout << " b4.i = " << b4.i << endl;

  C c1;
  cout << " c1.i = " << c1.i << endl;
}
