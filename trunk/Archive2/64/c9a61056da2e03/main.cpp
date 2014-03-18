#include <random>
#include <vector>
#include <iostream>

struct foo
{
//private:
    unsigned random = random_value();
    static unsigned random_value() {
        static std::mt19937 engine{std::random_device{}()};
        static std::uniform_int_distribution<unsigned> distribution{0, 10};
        return distribution(engine);
    }
};

int main()
{
    std::vector<foo> foos(10);
    
    for(auto const& f : foos) {
        std::cout << f.random << ' ';
    }
}
