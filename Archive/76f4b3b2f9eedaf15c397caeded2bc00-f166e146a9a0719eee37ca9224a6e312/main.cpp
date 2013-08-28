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
    {
        std::vector<thing> vec;
        //vec.reserve(10);
        vec.emplace_back();
        vec.emplace_back();
        vec.emplace_back();
        std::cout << "-" << std::endl;
        for(auto& elem : vec) elem.work();
    }
    std::cout << std::endl;
    {
        std::vector<thing> vec;
        vec.reserve(10);
        vec.emplace_back();
        vec.emplace_back();
        vec.emplace_back();
        std::cout << "-" << std::endl;
        for(auto& elem : vec) elem.work();
    }
}
