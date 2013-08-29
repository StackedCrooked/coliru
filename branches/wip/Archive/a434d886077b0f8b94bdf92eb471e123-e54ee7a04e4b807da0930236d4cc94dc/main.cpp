#include <utility>

constexpr unsigned mask(unsigned n)
{
    return (1 << n);
}

template<typename ...Args>
constexpr unsigned mask(unsigned head, Args&& ...tail)
{
    return mask(head) | mask(std::forward<Args>(tail)...);
}

int main()
{
    return mask(1, 2, 3);
}