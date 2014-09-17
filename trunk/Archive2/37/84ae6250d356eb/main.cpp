#include <memory>
#include <cassert>

std::shared_ptr<int> foo() {
    return {1 * 2 - 2};
}

int main()
{
    auto ptr = foo();
    assert(!ptr);
    return 0;
}
