#include <map>

struct Foo
{
    constexpr static int foo = 1;
};

static std::map<int, int> map {{1, Foo::foo}};

int main()
{
    return Foo::foo;
}
