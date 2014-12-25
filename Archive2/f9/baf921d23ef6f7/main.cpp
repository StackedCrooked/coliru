#include <iostream>
#include <type_traits>
#include <utility>

template <typename T, typename... Args>
static auto call(T&& t, int, Args&&... args)
    -> decltype(void(std::forward<T>(t).open_file(std::forward<Args>(args)...)))
{
    std::forward<T>(t).open_file(std::forward<Args>(args)...);
}

template <typename T, typename... Args>
static void call(T&& t, void*, Args&&... args)
{
    std::cout << "open_file() not called" << std::endl;
}

template <typename T, typename... Args>
static void eval(T&& t, Args&&... args)
{
    call(std::forward<T>(t), 0, std::forward<Args>(args)...);
}

class does_match
{
public:
    void open_file(int i) const { std::cout << "MATCHES!" << std::endl; };
};

class doesnt_match
{
public:
    void open_file() const { std::cout << "DOESN'T!" << std::endl; };
};

int main()
{
    does_match   it_does;
    doesnt_match it_doesnt;

    eval(it_does, 1);
    eval(it_doesnt, 2);
    eval(it_does);
    eval(it_doesnt);
}
