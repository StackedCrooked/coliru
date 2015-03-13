#include <iostream>
 
// objects of type S can be allocated at any address
// because both S.a and S.b can be allocated at any address
struct S {
  char a; // size: 1, alignment: 1
  char b; // size: 1, alignment: 1
}; // size: 2, alignment: 1
 
// objects of type X must be allocated at 4-byte boundaries
// because X.n must be allocated at 4-byte boundaries
// because int's alignment requirement is (usually) 4
struct X {
  int n;  // size: 4, alignment: 4
  char c; // size: 1, alignment: 1
  // three bytes padding
}; // size: 8, alignment: 4 
 
int main()
{
    std::cout << "sizeof(S) = " << sizeof(S)
              << " alignof(S) = " << alignof(S) << '\n';
    std::cout << "sizeof(X) = " << sizeof(X)
              << " alignof(X) = " << alignof(X) << '\n';
}