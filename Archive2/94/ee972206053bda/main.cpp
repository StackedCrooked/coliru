#include <cstdio>

struct foo
{
    void bar()
    {
        // same as [=]
        // same as [&]
        [this]
        {
            ++i;
        }(); // you can call a lambda without storing it anywhere (temporary)
    }

    int i;
};

int main(int, char**)
{
    int x = 0;

    printf("before calling anything x is %d.\n", x);

    // same as auto byVal = [&x]() mutable -> int
    auto byRef = [&]() -> int
    {
        ++x;
        return x;
    };

    auto res = byRef();
    printf("byRef returns %d and x is %d.\n", res, x);

    // same as auto byVal = [x]() mutable -> int
    auto byVal = [=]() mutable -> int
    {
        ++x;
        return x;
    };

    auto res2 = byVal();
    printf("byVal returns %d and x is %d.\n", res2, x);

    foo object;
    object.i = 3;
    object.bar();

    printf("foo::bar changes foo::i from 3 to %d.\n", object.i);

    return 0;
}
