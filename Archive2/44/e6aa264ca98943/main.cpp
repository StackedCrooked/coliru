#include <vector>
#include <type_traits>
int main() {
  using namespace std;
  vector<bool> a = {true, false, true, false};
  auto value = a[2];
  decltype(auto) reference = a[2];
  static_assert(is_same<decltype(reference), vector<bool>::reference>::value,
                "pass -> correct!");
  static_assert(is_convertible<decltype(value), vector<bool>::value_type>::value, 
                "fails -> wrong!");
}