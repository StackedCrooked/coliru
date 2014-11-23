#include <cstdlib>

template <typename T>
struct test;

template <typename Argument, typename Return>
struct test<Return (Argument)>
{

};


int main()
{
  return EXIT_SUCCESS;
}
