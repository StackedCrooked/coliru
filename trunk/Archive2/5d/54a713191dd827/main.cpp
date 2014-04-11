#include <iostream>
using namespace std;

template <class T> T sum(const T& in) { return in; }
template <class T, class... P> auto sum(const T& t, const P&... p) { return t + sum(p...); }

int main() {
   cout << sum(5, 10.0, 22.2) << endl;
}
