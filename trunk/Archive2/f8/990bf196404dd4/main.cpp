#include <iostream>
#include <type_traits>

template <bool...> struct bool_pack {};
template <bool... Bs> struct all : std::is_same<bool_pack<true, Bs...>, bool_pack<Bs..., true>> {};

struct argument{} x, y, z;

struct func
{
    template <typename... Args>
    auto operator()(Args&&... args)
        -> typename std::enable_if<all<std::is_same<typename std::decay<Args>::type, argument>{}...>{}, func&>::type
    {
        std::cout << "f(x,y,z)\n";
        return *this;
    }
    
    template <typename... Args>
    auto operator()(Args&&... args)
        -> typename std::enable_if<!all<std::is_same<typename std::decay<Args>::type, argument>{}...>{}, func&>::type
    {
        std::cout << "f(1,2)\n";
        return *this;
    }
};

int main()
{
    func f;
    f(x, y, z);
    f(1, 2);
}
