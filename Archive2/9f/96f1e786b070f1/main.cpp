#include <tuple>
#include <iostream>

std::ostream& operator<<(std::ostream& out, std::tuple<> const& tuple)
{
    return out; // Nothing to do here
}

template<typename First, typename... Types>
std::ostream& operator<<(std::ostream& out, std::tuple<First, Types...> const& tuple)
{
    out << std::get<0>(tuple) << " ";

    // The cast that I don't like
    return out << (std::tuple<Types...>&) tuple;
}

int main()
{
    auto tuple = std::make_tuple(1, 2.3, "Hello");
    std::cout << tuple << std::endl;
    return 0;
}