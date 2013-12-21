#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>

template<typename It>
It random_iterator(It b, It e) {
    thread_local static std::mt19937 engine(std::random_device{}());
    auto dist = std::distance(b, e);
    std::advance(b, std::uniform_int_distribution<decltype(dist)>{0, dist-1}(engine));
    return b;
}

int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    for(auto i=0; i<10; ++i) {
        std::cout << *random_iterator(words.begin(), words.end()) << std::endl;
    }
}
