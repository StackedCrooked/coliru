#include <iostream>
int doit(int x, ...) { return x; }
template<class X, class Y> auto doit(X x, Y y)
-> decltype(doit(x) + doit(y)) // Only this line was added
{ return doit(x) + doit(y); }
int main() {
    std::cout << doit(1, nullptr) << std::endl;
}
