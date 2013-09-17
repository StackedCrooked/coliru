#include <iostream>


struct test {
    test() {
        std::cout << "test object constructed @ " << this << std::endl;
    }
    
    ~test() {
        std::cout << "test object destroyed @ " << this << std::endl;
    }
};


int main() {
    test& t = *(new test);
    delete &t;
}