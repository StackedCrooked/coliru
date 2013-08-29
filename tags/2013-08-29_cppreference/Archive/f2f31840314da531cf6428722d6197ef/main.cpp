#include <string>

std::string do_it(double d);

#undef NDEBUG
#include <cassert>

int main() {
    assert(do_it(1.2) == "1.2");
}

// -- you can write the solution below this line --