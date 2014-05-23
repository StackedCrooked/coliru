#include <cstddef>

struct foo
{
    foo(std::nullptr_t) {}
};

int main()
{
    foo const& f = nullptr;
}