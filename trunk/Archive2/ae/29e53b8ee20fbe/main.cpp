#include <functional>

struct A {};
struct B
{
    B(A const&) {}
};

void foo(B const&) {}
void bar(B const& = A()) {}

int main()
{
    foo( A() );
    bar();
}