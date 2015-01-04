#include <iostream>
#include <functional>
#include <type_traits>
#include <utility>

class foo
{
public:    
    template <typename T>
    auto addListener(int e, T&& listener)
        -> typename std::enable_if<std::is_void<decltype(std::forward<T>(listener)(0, 0, 0))>{}>::type
    {
        [&](int msg, int wp, int lp) -> int {
                std::cout << "void\n";
                listener(msg, wp, lp);
                return 123;
            } (1, 2, 3);
    }
    
    template <typename T>
    auto addListener(int e, T&& listener)
        -> typename std::enable_if<!std::is_void<decltype(std::forward<T>(listener)(0, 0, 0))>{}>::type
    {
        [&](int msg, int wp, int lp) -> int {
                std::cout << "int\n";
                listener(msg, wp, lp);
                return 123;
            } (1, 2, 3);
    }
};

int main()
{
    foo f;
    f.addListener(1, [](int, int, int) -> int { return {}; });
    f.addListener(2, [](int, int, int) -> void { });
}
