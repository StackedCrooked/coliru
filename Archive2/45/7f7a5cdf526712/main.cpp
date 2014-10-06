#include <algorithm>
#include <iostream>
#include <list>
#include <random>
#include <type_traits>

template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
class random_generator {
    using distribution_type = typename std::conditional<
            std::is_integral<T>::value,
            typename std::uniform_int_distribution<T>,
            typename std::uniform_real_distribution<T>
        >::type;
    
    std::default_random_engine engine;
    distribution_type distribution;
    
public:
    auto operator()() -> decltype(distribution(engine)) {
        return distribution(engine);
    }
};

template<typename Container, typename T = typename Container::value_type>
auto make_generator(Container const&) -> decltype(random_generator<T>()) {
    return random_generator<T>();
}

int main() {
    auto l = std::list<double>(10);
    
    std::generate(std::begin(l), std::end(l), make_generator(l));    
    
    for (auto const& i : l) {
        std::cout << i << " ";    
    }

    return 0;
}