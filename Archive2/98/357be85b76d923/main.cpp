#include <utility>

struct T
{
    T() = default;
    T(T&&) = default;
    T(const T&) = delete;
};

T foo(T in)
{
    T out;
    return out;
}

int main()
{
    T t1;
    T t2 = foo(std::move(t1));
}