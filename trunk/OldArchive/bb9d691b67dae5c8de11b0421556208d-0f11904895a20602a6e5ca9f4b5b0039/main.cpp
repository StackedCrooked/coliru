#include <iostream>
#include <thread>


struct test {
    void do_something(int num) {
        std::cout << "num: " << num << std::endl;
    }
};


int main() {
    test x;
    std::thread t(&test::do_something, &x, 1234);
    t.join();
}

