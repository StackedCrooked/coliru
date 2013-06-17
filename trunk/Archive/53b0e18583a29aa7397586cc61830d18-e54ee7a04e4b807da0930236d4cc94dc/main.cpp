#include <vector>
#include <iostream>
#include <tuple>

template <typename Iterator0, typename Iterator1>
std::vector<std::tuple<
    typename Iterator0::value_type,
    typename Iterator1::value_type>>
zip(
    Iterator0 begin0, Iterator0 end0,
    Iterator1 begin1, Iterator1 end1)
{
    std::vector<std::tuple<
        typename Iterator0::value_type,
        typename Iterator1::value_type>> result;
    while (begin0 != end0 && begin1 != end1)
    {
        result.emplace_back(*begin0, *begin1);
        ++begin0;
        ++begin1;
    }
    return result;
}

int main()
{
    std::vector<int> x;
    x.push_back(5);
    x.push_back(3);
    x.push_back(7);
    
    std::vector<double> y;
    y.push_back(1.0);
    y.push_back(1.1);
    y.push_back(1.2);
    y.push_back(1.3);
    
    auto xy = zip(x.begin(), x.end(), y.begin(), y.end());
    for (auto it = xy.begin(); it != xy.end(); ++it)
    {
        std::cout << std::get<0>(*it) << ", " << std::get<1>(*it) << std::endl;
    }
}