#include <iostream>
#include <memory>
#include <mutex>

struct Obj {
  void lock   () { std::cout << "lock\n"; }
  void unlock () { std::cout << "unlock\n"; }
};

static Obj a;

void func () {
  std::lock_guard<Obj> x (a);
  throw 123;
}

int main () {
  try { func (); } catch (...) { throw; } 
}