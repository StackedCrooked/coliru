template <class> struct Z {};
struct B : Z<int> {};
struct C : B, Z<int> {};
void f(Z<int> const &) {}
int main() { f(C()); }