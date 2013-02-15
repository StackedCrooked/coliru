// a few assertions to ensure *some* minimal sanity, i.e., this is not Hell++
#include <limits>
static_assert(std::numeric_limits<double>::is_iec559, "This is an IEC559/IEEE754 system");
static_assert(std::numeric_limits<double>::digits10 > 2, "double can represent more than two base10 digits");

// declaration for your code
#include <string>
std::string do_it(double d);

// declaration for some undisclosed code that may or may not make this more complicated
// this function does not cause undefined behaviour
// you are not allowed to implement it
void secret_sauce();

// make sure assertions are on
#undef NDEBUG
#include <cassert>

int main() {
    secret_sauce();

    // this is the test
    assert(do_it(1.2) == "1.2");
}

// solution goes in a separate TU