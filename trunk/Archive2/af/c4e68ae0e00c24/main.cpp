#include <type_traits>
#include <string>

template<class R, class T, class... A> std::enable_if<1, R(A...)> hck (R(T::*)(A...));

struct B {
  std::integral_constant<int, 100> func (int, float, std::string);
};

struct C : B {
  decltype(hck(&B::func))::type func = delete;

  /* NOTE: the above is shorter and "easier" to write than */
  // std::integral_constant<int, 100> func (int, float, std::string) = delete;
};

int
main (int argc, char *argv[])
{
  C {}.func (1, 2.3f, "world"); /* <- deleted! */
}