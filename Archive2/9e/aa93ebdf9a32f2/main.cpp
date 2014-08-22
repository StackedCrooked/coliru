#include <functional>
#include <iostream>


struct my_class {
    int func(int i) {
        return i;   
    }
};


int main() {
    using namespace std::placeholders;
    auto func = std::bind(&my_class::func, my_class(), _1);
    std::cout << func(42);
}