#include <numeric>
#include <functional>

int main()
{
    using namespace std;

    auto budget = { 1000, 1500, 2000, 1500, 2000, 1000,
                    3000, 1500, 1200, 1800, 2200, 2000 };
    auto sales  = { 1000, 1400, 2100, 2000, 1800,  900,
                    3500, 1300, 1000, 2000, 2000, 2500 }; 

    return inner_product(begin(sales), end(sales), begin(budget),
            0u,
            plus<int>(),
            [](auto s, auto b) { return s>=b? 1 : 0; });
}
