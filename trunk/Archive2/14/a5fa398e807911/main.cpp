#include <tuple>
#include <functional>
#include <iostream>

namespace std
{
    template<>
    struct hash<std::tuple<float, float, float>>
    {
        typedef std::tuple<float, float, float> argument_type;
        typedef std::size_t value_type;

        value_type operator()(argument_type const& s) const
        {
            value_type const h1 ( std::hash<float>()(std::get<0>(s)) );
            value_type const h2 ( std::hash<float>()(std::get<1>(s)) );
            value_type const h3 ( std::hash<float>()(std::get<2>(s)) );
            return h1 ^ (h2 << 1) ^ (h3 << 2);
        }
    };
}

int main()
{
    std::tuple<float, float, float> a{0.5, 2.0, 3.0}, b{0.5, 3.0, 2.0}, c{0.6, 2.0, 3.0};
    std::hash<std::tuple<float, float, float>> hash_fn;
    std::cout << hash_fn(a) << '\n' << hash_fn(b) << '\n' << hash_fn(c) << '\n';
}