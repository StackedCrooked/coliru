#include <array>

template <typename T, std::size_t N>
class point : public std::array<T, N>
{
public:
    template<typename ...Args>
    point(Args&&...t) : std::array<T,N>{{std::forward<Args>(t)...}}
    {
    }
};

int main()
{
    point<int,5>      p1 = {0, 1, 1, 2, 3};
    std::array<int,5> p2 = {{0, 1, 1, 2, 3}};
}
