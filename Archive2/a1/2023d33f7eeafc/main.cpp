#include <utility>

struct Y
{
    void f();
};

template<typename T>
struct X
{
    void f() noexcept(noexcept(std::declval<Y>().f()));
};

template<typename T>
void X<T>::f() noexcept(noexcept(std::declval<Y>().f()))
{
}

int main()
{
}