#include <iostream>
#include <memory>
#include <mutex>

struct Obj {
  void lock   () { std::cout << "lock "; }
  void unlock () { std::cout << "unlock "; }
};

static Obj a;

void func () {
  std::lock_guard<Obj> x (a);
  throw 123;
}

int main () {
  func (); 
}