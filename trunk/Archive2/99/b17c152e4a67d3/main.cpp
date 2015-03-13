#include <iostream>
#include <functional>
#include <vector>
#include <type_traits>

using namespace std;

template <bool is_enabled = true>
class Aggregator {
public:
    Aggregator(std::function<char*()> data) : data(data) { }

    void fun() {
        for (uint32_t i = 0; i < 100; i++)
            std::cout << *((int *)data() + i) << std::endl;

        funInternal();
    }

private:
    template<bool enabled = is_enabled>
    void funInternal(typename std::enable_if<enabled>::type* = 0) {
        std::cout << "Feature is enabled!" << std::endl;
    }

    template<bool enabled = is_enabled>
    void funInternal(typename std::enable_if<!enabled>::type* = 0) {
        std::cout << "Feature is disabled!" << std::endl;
    }

    std::function<char*()> data;
};

template <typename T> 
class Multivalue : public Aggregator<true> {
public:
    Multivalue() : Aggregator<true>([&]() { return (char *) v.data(); }) { }

    void add(T a) { v.push_back(a); }
private:
    std::vector<T> v;
};

int main() {
    std::vector<Multivalue<int>> m(100);
    // uncomment for segfault
    //m.reserve(10000);
    
    for (uint32_t i = 0; i < 100; i++) 
        for (uint32_t j = 0; j < 1000; j++) 
            m[i].add(j);

    for (uint32_t i = 0; i < 100; i++)
        m[i].fun();

    return 0;
}