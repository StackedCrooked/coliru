#include <iostream>

auto print = [](auto x)
{
    using namespace std;
    cout << x << endl;
};

int main()
{
    auto add = [](auto x, auto y)
    {
        return x + y;
    };
    auto sub = [](auto x, auto y)
    {
        return x - y;
    };
    auto apply = [](auto f, auto... args)
    {
        return f(args...);
    };

    print(apply(apply, apply, apply, add, 1, 2));
    print(apply(apply, apply, sub, 11, 2));
}