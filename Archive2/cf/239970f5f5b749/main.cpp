#include <iostream>
#include <array>

// First version
template<class Container>
auto get(std::size_t i, Container&& container) -> decltype(container[i]) {
    return container[i];
}

// Second version
template<class Container>
auto geto(std::size_t i, Container& container) -> decltype(container[i]) {
    return container[i];
}

template<class Container>
auto geto(std::size_t i, const Container& container) -> decltype(container[i]) {
    return container[i];
}

int main() {}