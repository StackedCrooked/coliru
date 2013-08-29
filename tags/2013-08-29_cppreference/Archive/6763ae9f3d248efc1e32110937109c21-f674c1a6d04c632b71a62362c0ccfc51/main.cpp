#include <array>
#include <iostream>
#include <utility>
using namespace std;

template<typename T, unsigned long N>
void foo(array<T,N> src) { 

  for (auto e : src)
    cout << e << endl;
}

template<class T, class... Tail>
auto make_array(T head, Tail... tail) -> std::array<T, 1 + sizeof...(Tail)>
{
     std::array<T, 1 + sizeof...(Tail)> a = {{ head, tail ... }};
     return a;
}

template<class T, class... Tail> 
void foo(T&& head, Tail&&... values) {

    foo(make_array(std::forward<T>(head), std::forward<Tail>(values)...));
}

int main() {

  foo('a', 'b');

  foo(1, 2, 3);
}

