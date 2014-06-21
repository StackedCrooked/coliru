#include <initializer_list>
#include <iostream>

int bar(int i) { return i + 1; }

void baz(int) {}

struct strange {};

strange overload_comma(int) { return strange{}; }

template <typename T>
void operator,(strange, T) {}

template <typename... Args>
void foo(Args&&... args)
{
    auto a = {bar(args)...};

    for (const auto& elt : a)
    {
        std::cout << elt << ' ';
    }

    auto v = {(baz(args), 0)...};
    (void) v;
    
    auto over = {(overload_comma(args), void(), 0)...};
    (void) over;
}

int main()
{
    foo(1, 2, 3);

    return 0;
}
