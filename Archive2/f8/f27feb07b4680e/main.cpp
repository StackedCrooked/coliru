#include <iostream>
#include <thread>

struct Obj {
  void operator()() {
    std::cerr << "WOO";
  }
};

int
main (int argc, char *argv[])
{
  Obj a;

  std::thread (&Obj::operator(), &a).join ();
}