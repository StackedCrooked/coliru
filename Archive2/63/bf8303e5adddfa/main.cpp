#include <initializer_list>
#include <iterator>
#include <utility>
#include <cassert>

std::pair<double, double> to_pair(std::initializer_list<const double> init)
{
    return std::pair<double, double>(*init.begin(), *std::next(init.begin()) );
}

constexpr bool pair_compile_check(std::initializer_list<const double> init)
{
    return init.size()==2 ? true : throw 0;
}

std::pair<double, double> to_pair_compile_check_ce2(std::initializer_list<const double> init)
{
    constexpr auto t = pair_compile_check(init); // <--- fails to compile
    return init.size()==2?std::pair<double, double>(*init.begin(), *std::next(init.begin())):throw 0;
}

int main()
{
    using namespace std;

    // Works, but tedious:
    constexpr auto init = {1., 2.};
    constexpr auto t = pair_compile_check(init);
    auto p = to_pair(init);
    // ******************
    
    // It should be:
    auto p5 = to_pair_compile_check_ce2({1.,2.});
    // but fails
}
