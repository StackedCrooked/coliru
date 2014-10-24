#include <tuple>
#include <type_traits>
#include <iostream>

int main()
{
    std::tuple<int, char> a;
    std::tuple<double> b;
    std::cout << std::is_same<decltype(std::tie(a, b)), 
                              std::tuple<std::tuple<int, char>&, std::tuple<double>&>>() << '\n';
    
//    tie(a, b) = std::make_tuple(1, 'a', 3.14);    // doesn't compile
    tie(a, b) = std::make_tuple(std::make_tuple(1, 'a'), std::make_tuple(3.14));
    std::cout << std::get<0>(a) << ' '
              << std::get<1>(a) << ' '
              << std::get<0>(b) << '\n';
}
