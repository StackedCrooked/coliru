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
        [&](int msg, int wp, int lp) -> int {
                std::cout << "void\n";
                listener(msg, wp, lp);
                return 123;
            } (1, 2, 3);
    }
    
    template <typename T, typename = typename std::enable_if<!std::is_void<typename std::result_of<T(int, int, int)>::type>::value>::type, typename = void>
    void addListener(int e, T&& listener)
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
