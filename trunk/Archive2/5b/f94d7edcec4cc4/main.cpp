#include <functional>
#include <iostream>
#include <vector>

class TestSuite {
    public:
        template<typename This, typename... Tests>
        TestSuite(This this_, Tests... tests) {
            add_tests(this_, tests...);
        }

        size_t num_tests() const { return test_functions.size(); }
        void run() {
            for (auto& test_function : test_functions) {
                test_function();
            }
        }

    private:
        std::vector<std::function<void()>> test_functions;

        template<typename This, typename H, typename... T> void add_tests(This this_, H test1, T... tests) {
            test_functions.emplace_back(std::bind(std::mem_fn(test1), this_));
            add_tests(this_, tests...);
        }

        template<typename This, typename H> void add_tests(This this_, H test1) {
            test_functions.emplace_back(std::bind(std::mem_fn(test1), this_));
        }
};

class test_foo : public TestSuite {
    public:
        test_foo()
            : TestSuite(
                this,
                &test_foo::simple_test,
                &test_foo::another_test
                ) {}

        void simple_test() {
            std::cout << "In simple_test()...\n";
            std::cout << x << "\n";
            x *= 2;
        }

        void another_test() {
            std::cout << "Another test...\n";
            std::cout << x << "\n";
        }

        double x;
};

int main()
{
    test_foo tests;
    std::cout << tests.num_tests() << "\n";
    tests.x = 3;
    tests.run();
}
