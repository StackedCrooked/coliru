struct S { constexpr S() : d(this) {} void *d; };

extern S s;

struct Check {
  Check() { if (s.d != &s) throw 1; }
} check;

S s;

int main() { }