#include <iostream>
using namespace std;
struct A {
   virtual void operator()(int a, int b)const { cout << a + b << endl; }
};
struct B : A {
   void operator()(int a, int b)const { cout << a - b << endl; }
};
void f(int a, int b, const A &obj) {
   obj(a, b);
}
int main() {
   int a = 5, b = 3;;
   B obj;
   f(a, b, obj); // should give 2, but gives 8 (uses A's function even if it's virtual)
}