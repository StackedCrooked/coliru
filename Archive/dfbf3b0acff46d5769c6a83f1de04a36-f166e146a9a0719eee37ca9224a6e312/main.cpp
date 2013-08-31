#include <functional>
#include <iostream>
#include <vector>

class cl {
public:
    cl() {
        std::cout << this << std::endl;
    }
    void work() {
        std::cout << this << std::endl;
    }
};

int main() {
    std::vector<cl> n;
    n.push_back(cl{});
    n[0].work();
}
