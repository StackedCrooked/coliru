#include<functional>
#include<iostream>
struct id {};
template <typename T> void each(std::function<void(T)> ){ std::cout << __PRETTY_FUNCTION__ << std::endl; }
template <typename T> void each(std::function<void(T, id)> ){ std::cout << __PRETTY_FUNCTION__ << std::endl; }
template <typename T> void each(std::function<void(T&)> ){ std::cout << __PRETTY_FUNCTION__ << std::endl; }
template <typename T> void each(std::function<void(T&, id)> ){ std::cout << __PRETTY_FUNCTION__ << std::endl; }
int main() {
    each<int>([](int, id){});
}