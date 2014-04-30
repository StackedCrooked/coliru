#include <numeric>
#include <functional>
#include <algorithm>

int main()
{
    using namespace std;

    auto budget = { 1000.0, 1500.0, 2000.0, 1500.0, 2000.0, 1000.0,
                    3000.0, 1500.0, 1200.0, 1800.0, 2200.0, 2000.0 };
    auto sales  = { 1000.0, 1400.0, 2100.0, 2000.0, 1800.0,  900.0,
                    3500.0, 1300.0, 1000.0, 2000.0, 2000.0, 2500.0 }; 

    std::vector<bool> met;

    transform(begin(sales), end(sales), begin(budget), back_inserter(met), greater_equal<int>());

    return count(begin(met), end(met), true);
}
