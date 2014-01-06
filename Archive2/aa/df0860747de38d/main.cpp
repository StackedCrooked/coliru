#include <iostream>
#include <thread>

struct Obj {
  Obj () {
    std::cerr << "this = " << this << std::endl;
  }

  void operator()() {
    std::cerr << "this = " << this << std::endl;
  }
};

int
main (int argc, char *argv[])
{
  Obj a;

  std::thread (&Obj::operator(), &a).join ();
}