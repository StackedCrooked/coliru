#include <tuple>
#include <utility>

int main()
{
    std::tuple<> t;
    std::tuple<> u{ std::move(t) };
}