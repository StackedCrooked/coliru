#include <type_traits>
#include <utility>
struct S {
  int a[10];
};
int main() {
  S s;
  static_assert(std::is_same<decltype((std::move(s).a)), int (&&) [10]>::value, "not an array rvalue");
}
