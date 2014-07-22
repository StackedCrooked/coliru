#include <string>
struct A {
  std::string abc = "abc";
};
struct B {
  int b = 0;
};
struct C {
  int c;
};
struct D {
  D() = default;
  std::string abc = "abc";
};
struct E {
  E() {}
  std::string abc = "abc";
};
struct F {
  F();
  std::string abc = "abc";
};
inline F::F() = default;
int main()
{
  A const a1; // clang errors
  A const a2 {}; // clang is happy
  B const b; // clang errors
  C const c; // clang and gcc errors, msvc warns
  D const d; // clang errors
  E const e; // clang is happy
  F const f; // clang is happy (default constructor is not technically user defined)
}