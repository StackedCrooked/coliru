#include <vector>
#include <iostream>
#include <functional>

struct aggregate {
    int foo;
    char bar[2];
};

class test {
private:
    std::vector<aggregate> v;
    std::function<void(aggregate&)> lambda;
public:
    test() :
        lambda([this] (aggregate& a) { v.push_back(a); })
    {
        v.reserve(8);
    }
};

int main() {
    test t;
}
