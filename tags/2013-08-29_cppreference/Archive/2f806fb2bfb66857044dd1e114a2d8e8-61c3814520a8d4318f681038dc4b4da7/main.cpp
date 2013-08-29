#include <iostream>
#include <memory>

#include <boost/variant/variant.hpp>
#include <boost/variant/get.hpp>

int main()
{
    boost::variant<std::unique_ptr<int>> v(std::unique_ptr<int> { new int(42) });
    auto u = std::move(v);
    std::cout << *boost::get<std::unique_ptr<int>>(u) << '\n';
}