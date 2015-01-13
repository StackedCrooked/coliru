#include <utility>
#define ASSERT(foo) do{ if (!(foo)) *(char*)0 = 0; } while(0)

#define using_overload(alias, function) auto alias = [](auto&&... args) { return (function)(std::forward<decltype(args)>(args)...); }

int main() {
    using_overload(swap_ints, std::swap<int>);
    
    
    int a = 0, b = 1;
    swap_ints(a, b);
    ASSERT(a == 1 && b == 0);
}