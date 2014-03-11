#include <iostream>
#include <complex>

using namespace std;

template <typename T> void print(T t) { cout << t; }

template <typename T1, typename T2, typename ...Ts>
void print(T1 t1, T2 t2, Ts... ts) {
  print(t1); cout << ", "; print(t2, ts...);
}

template <typename ...Ts>
void print_vec(Ts... ts) {
  cout << "("; print(ts...); cout << ")";
}

int main() {
    print_vec(1.0, 2.0f, 3, "four", complex<float>(5,6));
}