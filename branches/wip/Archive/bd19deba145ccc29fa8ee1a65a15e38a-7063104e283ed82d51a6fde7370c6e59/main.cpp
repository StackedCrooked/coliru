#include <iostream>
#include <functional>

class Test {
private:
    std::function<void(void)> callback;
    size_t current;
public:
    void onFive(std::function<void(void)> f) {
        callback = f;
    }
    void addNumber(size_t number) {
        if(number == 5 && callback)
            callback();
    }
    void test() {
        std::cout << "Internal method called\n";
    }
};

int main() {
    Test t;
    t.onFive([&](){
        t.test();
    });
    for(size_t i = 0; i <= 10; ++i) {
        std::cout << "Number: " << i << '\n';
        t.addNumber(i);
    }
}