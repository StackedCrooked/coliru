#include <cassert>

struct foo { int x; };

int main () {
    foo f;
    assert(f.x == 0);
}