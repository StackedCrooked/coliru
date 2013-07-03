#include <iostream>
#include <thread>


struct test {
    int some_num;
    
    test(int n) : some_num(n) {}
    
    void do_something(int num) {
        std::cout << "some_num * num: " << some_num * num << std::endl;
    }
};


int main() {
    test x(2);
    std::thread t(&test::do_something, &x, 1234);
    t.join();
}

