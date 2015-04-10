#include "/Archive2/e1/c88d7c5c24e62b/main.cpp" /* http://coliru.stacked-crooked.com/a/e1c88d7c5c24e62b */
#include <iostream>

struct tag_1 {};
struct tag_2 {};

int main () {
  using C1 = count_tag<tag_1>;
  using C2 = count_tag<tag_2>;

  refp_incr (C1);
  refp_incr (C1);
  refp_incr (C1);

  refp_incr (C2);

  {
    int constexpr c1 = refp_count(C1);
    int constexpr c2 = refp_count(C2);

    std::cout << "C1 = " << c1 << ", ";
    std::cout << "C2 = " << c2 << "\n";
  }

  refp_incr (C1);
  refp_incr (C2);
  refp_incr (C2);

  {
    int constexpr c1 = refp_count(C1);
    int constexpr c2 = refp_count(C2);

    std::cout << "C1 = " << c1 << ", ";
    std::cout << "C2 = " << c2 << "\n";
  }
}