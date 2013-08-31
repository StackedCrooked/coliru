// a few assertions to ensure *some* minimal sanity, i.e., this is not Hell++
#include <limits>
static_assert(std::numeric_limits<double>::is_iec559, "This is an IEC559/IEEE754 system");
static_assert(std::numeric_limits<double>::digits10 > 2, "double can represent more than two base10 digits");

// declaration for your code
#include <string>
std::string do_it(double d);

// declaration for some secret production of a test case
// this function does not cause undefined behaviour
// you are not allowed to implement it
#include <tuple>
std::tuple<double, std::string> secret_sauce();
// it produces a number less than 10 that has an exact base-10 representation with only two digits
// and a string with its base-10 representation as it would be in C++ source code
// (no suffixes, no redundant zeros, no omitted zero on the units)

// make sure assertions are on
#undef NDEBUG
#include <cassert>

int main() {
    double input;
    std::string output;
    std::tie(input, output) = secret_sauce();

    // example test
    assert(to_string(0.5) == "0.5");

    // the real test
    assert(do_it(input) == output);
}

// solution goes in a separate TU
// you can use boost