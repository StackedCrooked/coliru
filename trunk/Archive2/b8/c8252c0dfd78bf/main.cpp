#include <iostream>

struct foo
{
    template<typename... Ts>
    foo(Ts&&... ts)
    {
        unpack(std::forward<Ts>(ts)...);
    }


    template<typename T, typename... Ts>
    std::enable_if_t<std::is_same<std::decay_t<T>, char>::value> unpack(T*, Ts&&... ts)
    {
        std::cout << "(const) char*" << std::endl;
        unpack(std::forward<Ts>(ts)...);
    }

    template<typename T, typename... Ts>
    void unpack(T&&, Ts&&... ts)
    {
        std::cout << "T&&" << std::endl;
        unpack(std::forward<Ts>(ts)...);
    }

    void unpack()
    {
    }
};

int main()
{
    char buf[1024] = {};
    const char* str = "foo";
    foo f(buf, str);
    return 0;
}