#include <cassert>

int main () {
    struct foo{};
    using the_type = int (foo::*)();
    auto it = the_type(); 
    the_type it2;
    assert(it == nullptr);
    assert(it2 == nullptr);
}