#include <functional>
#include <utility>
#include <vector>

namespace detail {
    inline void register_test_or_run_tests(std::function<void()> test, bool run) {
        static std::vector<std::function<void()>> tests;
        if (run) {
            for (auto& test : tests) {
                test();
            }
        } else {
            tests.push_back(std::move(test));
        }
    }
}

#define TOKENPASTE(x, y) x ## y

#define unittest_(id)                                                   \
    namespace TOKENPASTE(test_, id) {                                    \
        struct test {                                                   \
            void operator()();                                          \
        };                                                              \
                                                                        \
        struct registerer {                                             \
            registerer() {                                              \
                ::detail::register_test_or_run_tests(test(), false);    \
            }                                                           \
        } the_registerer;                                               \
    }                                                                   \
                                                                        \
    void TOKENPASTE(test_, id) ::test::operator()() 

#define unittest unittest_(__COUNTER__)

void run_tests() {
    ::detail::register_test_or_run_tests(nullptr, true);
}

// usage example
#include <cassert>
#include <iostream>

unittest {
    std::cout << "A unit test!\n";
    assert(1 + 2 == 3);
}

unittest {
    std::cout << "Another unit test!\n";
    assert(1 + 2 == 4);
}

int main() {
#ifndef NDEBUG
    run_tests();
#endif

    // continue program as normal
    std::cout << "Hello, world!" << '\n';
}
