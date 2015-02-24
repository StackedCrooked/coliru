#include <iostream>
using namespace std;    
struct A{
  A() {cout << "A" << endl;}
  A(int) {cout << "A+" << endl;}
};

struct B : virtual A{
  B() : A() {cout << "B" << endl;}
};
struct C : virtual A{
  C() : A() {cout << "C" << endl;}
};
struct D : virtual A{
  D() : A() {cout << "D" << endl;}
};
struct E : B, virtual C, D{
  E(){cout << "E" << endl;}
};
struct F : D, virtual C{
  F(){cout << "F" << endl;}
};
struct G : E, F{
  G() : A(1) {cout << "G" << endl;}
};

int main(){
  G g;
  return 0;
}