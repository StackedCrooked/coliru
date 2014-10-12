#include <vector>
#include <iostream>

struct test {
    test();
    virtual void run() = 0;
};

std::vector<test*> v;

int main() {
    for (auto p : v) {
        p->run();
    }
}

struct my_test : test {
    void run() override { std::cout << __PRETTY_FUNCTION__ << std::endl; }
} static my_test_var;

test::test() { v.push_back(this); }
