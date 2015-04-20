#include <iostream>
#include <random>
#include <algorithm>
#include <vector>
#include <type_traits>

template <typename, typename = std::true_type>
struct dist;

template <typename T>
struct dist<T, typename std::is_integral<T>::type>
{
    using type = std::uniform_int_distribution<T>;
};

template <typename T>
struct dist<T, typename std::is_floating_point<T>::type>
{
    using type = std::uniform_real_distribution<T>;
};

template<typename TContainer>
void uniform_random(TContainer& container, 
const typename TContainer::value_type min, 
const typename TContainer::value_type max) {
    std::random_device rd;
    std::mt19937 gen(rd());

    typename dist<typename TContainer::value_type>::type distribution(min, max);

    auto lambda_norm_dist = [&](){ return distribution(gen); };
    std::generate(container.begin(), container.end(), lambda_norm_dist);
}

int main() {
    std::vector<float> a(10);
    uniform_random(a,0,10);
    for (auto el : a) { std::cout << el << " "; }
    
    std::cout << std::endl;
    
    std::vector<int> b(10);
    uniform_random(b,0,10);
    for (auto el : b) { std::cout << el << " "; }
}