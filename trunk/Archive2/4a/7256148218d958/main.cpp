#include <cassert>

int main () {
    struct foo{};
    using the_type = int (foo::*)();
    auto it = the_type(); 
    assert(it == nullptr);
}