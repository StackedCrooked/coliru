#include <functional>


template <typename T, typename...Args>
std::function<T*()> MakeFactoryMethod(Args&&... args)
{
    return std::bind([](Args&... args2)
        {
            return new T(std::forward<Args>(args2)...);
        },
        std::forward<Args>(args)...);
}

struct foo {
    explicit foo(int) {}
};

int main()
{
    auto test = MakeFactoryMethod<foo>(5);
    delete test();
}