#include <iostream>
 
// this overload is always in the set of overloads
// ellipsis parameter has the lowest ranking for overload resolution
void test(...)
{
    std::cout << "Catch-all overload called\n";
}
 
// this overload is added to the set of overloads if
// C is a reference-to-class type and F is a member function pointer
template<class C, class F>
auto test(C c, F f) -> decltype((void)(c.*f)(), void())
{
    std::cout << "Reference overload called\n";
}
 
// this overload is added to the set of overloads if
// C is a pointer-to-class type and F is a member function pointer
template<class C, class F>
auto test(C c, F f) -> decltype((void)((c->*f)()), void())
{
    std::cout << "Pointer overload called\n";
}
 
struct X { void f() {} };
 
int main(){
  X x;
  test( x, &X::f);
  test(&x, &X::f);
  test(42, 1337);
}