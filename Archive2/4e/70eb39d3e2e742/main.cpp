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
        std::cout << "void\n";
        [&](int msg, int wp, int lp) -> int {
            listener(msg, wp, lp);
            return 0;
        }(0, 0, 0);
    }
    
    template <typename T>
    auto addListener(int e, T&& listener)
        -> typename std::enable_if<!std::is_void<decltype(std::forward<T>(listener)(0, 0, 0))>{}>::type
    {
        std::cout << "int\n";
        [&](int msg, int wp, int lp) -> int {
            std::function<int()> func = std::bind(listener, msg, wp, lp);
            return func();
        }(0, 0, 0);
    }
};

int main()
{
    foo f;
    f.addListener(1, [](int, int, int) -> int { return {}; });
    f.addListener(2, [](int, int, int) -> void { });
}
