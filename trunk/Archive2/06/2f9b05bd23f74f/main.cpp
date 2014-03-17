#include <cassert>

template <class T>
auto be_equal(T const &expect) {
    return [&](auto const & actual) {
        return expect == actual;   
    };
}

int main() {
    assert(be_equal(5)(5.0));
}