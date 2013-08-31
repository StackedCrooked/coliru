#include <cassert>
#include <cstddef>
#include <iostream>
#include <vector>

using namespace std;

template <size_t... I>
struct index_sequence {};

template <size_t N, size_t... I>
struct make_index_sequence : public make_index_sequence<N - 1, N - 1, I...> {};

template <size_t... I>
struct make_index_sequence<0, I...> : public index_sequence<I...> {};

int f(int a, int b) {
  return a + b;
}
void f(int a, int b, int c) {
  cout << "args = (" << a << ", " << b << ", " << c << ")\n";
}

template <typename T, size_t... I>
auto call_(const vector<T>& vec, index_sequence<I...>)
  -> decltype(f(vec[I]...)) {
  return f(vec[I]...);
}

template <size_t Arity, typename T>
auto call(const vector<T>& vec)
  -> decltype(call_(vec, make_index_sequence<Arity>())) {
  assert(vec.size() >= Arity);
  return call_(vec, make_index_sequence<Arity>());
}

int main() {
  vector<int> values = {0, 1, 2, 3, 4, 5};
  call<3>(values);
  cout << "call<2>(values) = " << call<2>(values) << endl;
}
