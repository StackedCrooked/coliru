#include <vector>
#include <memory>

template<class B, class... Ds>
std::vector<std::shared_ptr<B>>& instances()
{
    static std::vector<std::shared_ptr<B>> a = { std::shared_ptr<B>(new Ds)... };
    return a;
}

struct B {};

struct D1 : B {};
struct D2 : B {};

int main()
{
    auto&& i = instances<B, D1, D2>();
}