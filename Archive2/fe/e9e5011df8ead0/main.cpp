#include <functional>
#include <iostream>
#include <vector>

#define MEM_FN(fn) std::bind(std::mem_fn(&fn), this)

class TestSuite {
    public:
        template<typename... Tests>
        TestSuite(Tests... tests) {
            add_tests(tests...);
        }

        size_t num_tests() const { return test_functions.size(); }
        void run() {
            for (auto& test_function : test_functions) {
                test_function();
            }
        }

    private:
        std::vector<std::function<void()>> test_functions;

        template<typename H, typename... T> void add_tests(H test1, T... tests) {
            test_functions.emplace_back(test1);
            add_tests(tests...);
        }

        template<typename H> void add_tests(H test1) {
            test_functions.emplace_back(test1);
        }
};

class test_foo : public TestSuite {
    public:
        test_foo()
            : TestSuite(
                MEM_FN(test_foo::simple_test),
                MEM_FN(test_foo::another_test)
                ) {}

        void simple_test() {
            std::cout << "In simple_test()...\n";
        }

        void another_test() {
            std::cout << "Another test...\n";
        }
};

int main()
{
    test_foo tests;
    std::cout << tests.num_tests() << "\n";
    tests.run();
}
