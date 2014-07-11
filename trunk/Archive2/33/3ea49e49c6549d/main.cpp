#include <iostream>
struct t { const char* f() &; const char* f() &&; }
void g() {
    t obj;
    std::cout << obj.f() << t().f();
}