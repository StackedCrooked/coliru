#include <iostream>
struct A {
  operator void*() {
    return void*(5);
 } 
};
int main() 
{
  A a;
  A* ptr = & a;
  char* a1 = static_cast<char*>((void*)ptr));
  char* a2 = reinterpret_cast<char*>(ptr);
  using namespace std;
  cout << a1 << ' ' << a2 << endl;
} 