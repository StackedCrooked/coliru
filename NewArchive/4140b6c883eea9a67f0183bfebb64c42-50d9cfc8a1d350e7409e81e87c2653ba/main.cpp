#include <iostream>

int
func ()
{
  throw  1;
  return 0;
}

struct Obj {
  Obj ()
    try : i(func ())
  {
    // ... 
  }
  catch (...)
  {
    std::cerr << "we caught it! ";
  }

  int i;
};

int
main (int argc, char *argv[])
{
    Obj x;
    // pretend the exception was not rethrown
    std::cout << x.i; // wat?
}