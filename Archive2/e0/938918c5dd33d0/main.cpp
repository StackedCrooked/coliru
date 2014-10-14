#include <cassert>

struct Base1 { int x; };
struct Base2 { int y; };
struct Derived : Base1, Base2 { int z; };

int main() { Derived d; assert((void*)&d != (void*)static_cast<Base2*>(&d)); }