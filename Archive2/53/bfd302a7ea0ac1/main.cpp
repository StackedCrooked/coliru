#include <iostream>
#include <random>
#include <algorithm>
#include <vector>

#include <type_traits>
#include <typeinfo>

template<class T, class Enable = void>
struct uniform_distribution_helper {};

template<class T>
struct uniform_distribution_helper<T, class std::enable_if<std::is_floating_point<T>::value >::type> {
    using type = std::uniform_real_distribution<T>;
};

template<class T>
struct uniform_distribution_helper<T, class std::enable_if<std::is_integral<T>::value >::type> {
    using type = std::uniform_int_distribution<T>;
};

template<typename TContainer>
void uniform_random(TContainer& container, 
const typename TContainer::value_type min, 
const typename TContainer::value_type max) {
    using uniform_distribution = typename uniform_distribution_helper<typename TContainer::value_type>::type;
    std::cout << typeid(uniform_distribution).name() << '\n';
    std::random_device rd;
    std::mt19937 gen(rd());

    // Below line does not work with integers container
    uniform_distribution distribution(min, max);

    auto lambda_norm_dist = [&](){ return distribution(gen); };
    std::generate(container.begin(), container.end(), lambda_norm_dist);
}

int main() {
    std::vector<float> a(10);
    uniform_random(a,0,10);
    for (auto el : a) { std::cout << el << " "; }
    
    std::cout << '\n';
    std::vector<int> b(10);
    uniform_random(b,0,10);
    for (auto el : b) { std::cout << el << " "; }
}