#include <iostream>
struct t { ~t(); };
void g() {
    t obj;
}