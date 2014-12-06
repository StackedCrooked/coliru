#include <cassert>
#include <vector>

std::vector<int> foo() {
    return {1,2,3,4};
}

template<class T>
bool is_equal(const T& a, const T& b) {
    return a == b;
}

int main()
{
    assert((foo() == std::vector<int>{1,2,3,4}));

    assert(is_equal(foo(), {1,2,3,4}));

    assert([&](std::vector<int> v) -> bool {
        return foo() == v;
    }({1,2,3,4}));
}