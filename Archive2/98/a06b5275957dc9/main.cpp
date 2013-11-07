void use(const int&) {}

struct A { static const int t = 0; };

int main() { use(A::t); }