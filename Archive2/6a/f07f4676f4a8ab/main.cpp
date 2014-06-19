#include <utility>
class Foo
{
public:
 Foo() = default;
 Foo(Foo&&) = default;

 Foo(const Foo&) = delete;
 Foo& operator=(const Foo&) = delete;
};

int main()
{
 Foo foo1;
 Foo foo2 ( std::move(foo1) );
}