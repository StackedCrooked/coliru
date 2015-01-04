#include <iostream>
#include <functional>
#include <type_traits>
#include <utility>

class foo
{
public:    
    template <typename T, typename = typename std::enable_if<std::is_void<typename std::result_of<T(int, int, int)>::type>::value>::type>
    void addListener(int e, T&& listener)
    {
        std::cout << "void\n";
        [&](int msg, int wp, int lp) -> int {
            listener(msg, wp, lp);
            return 0;
        }(0, 0, 0);
    }
    
    template <typename T, typename = typename std::enable_if<!std::is_void<typename std::result_of<T(int, int, int)>::type>::value>::type, typename = void>
    void addListener(int e, T&& listener)
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
