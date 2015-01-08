#include <iostream>
#include <algorithm>
#include <functional>

struct BulkPosition
{
    double x = 0.0;
    double y = 0.0;
};

struct GeneralPosition
{
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
};

template<typename... Ts, typename F>
bool all_of(F predicate, BulkPosition const& p1, Ts const&... args)
{    
    auto x_true = predicate(p1.x, args.x...);
    auto y_true = predicate(p1.y, args.y...);
    
    return (x_true && y_true);
}

template<typename... Ts, typename F>
bool all_of(F predicate, GeneralPosition const& p1, Ts const&... args)
{    
    auto x_true = predicate(p1.x, args.x...);
    auto y_true = predicate(p1.y, args.y...);
    auto z_true = predicate(p1.z, args.z...);
    
    return (x_true && y_true && z_true);
}

int main()
{
    auto b1 = BulkPosition{0.0, 1.0};
    auto b2 = BulkPosition{2.0, 1.0};
    auto b3 = BulkPosition{3.0, 3.0};

    auto g1 = GeneralPosition{3.0, 3.0, 3.0};
    auto g2 = GeneralPosition{3.0, 3.0, 3.0};
    auto g3 = GeneralPosition{3.0, 3.0, 3.0};
    
    auto pred1 = [&] (double p1)
    {
        return (p1 > 0.0);
    };
    
    auto pred2 = [&] (double p1, double p2)
    {
        return (p1 < p2);
    };

    auto pred3 = [&] (double p1, double p2, double p3)
    {
        return (p1 < (p2 + p3));
    };
    
    std::cout << all_of(pred1, b1) << std::endl;
    std::cout << all_of(pred2, b1, b2) << std::endl;
    std::cout << all_of(pred3, b1, b2, b3) << std::endl;
    
    std::cout << all_of(pred1, g1) << std::endl;
    std::cout << all_of(pred2, g1, g2) << std::endl;
    std::cout << all_of(pred3, g1, g2, g3) << std::endl;
}