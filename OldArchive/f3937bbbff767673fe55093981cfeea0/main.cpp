#include <memory>

struct foo {
    std::unique_ptr<int> p;
};

foo f;

static_assert(noexcept(foo(std::move(f))),
              "Tis correct dammit, just man up and figure out the errors");

int main() {}
