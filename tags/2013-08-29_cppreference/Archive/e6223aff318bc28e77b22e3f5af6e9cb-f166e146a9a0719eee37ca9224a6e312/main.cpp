#include <iostream>
#include <vector>

class thing {
public:
    thing() {
        std::cout << this << std::endl;
    }
    void work() {
        std::cout << this << std::endl;
    }
};

int main() {
    std::vector<thing> vec;
    vec.emplace_back();
    for(auto& elem : vec) elem.work();
}
