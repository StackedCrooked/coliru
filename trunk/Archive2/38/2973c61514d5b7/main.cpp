#include <iostream>
 
struct test {
   virtual void f() { std::cout << "f\n"; }
   virtual void g() { std::cout << "g\n"; }
};
 
struct test2 {
   virtual void g() { std::cout << "g\n"; }
};
 
void callF(test *t) {
    t->f();
}
 
int main() {
    test2 t2;
	callF(reinterpret_cast<test*>(&t2));
}