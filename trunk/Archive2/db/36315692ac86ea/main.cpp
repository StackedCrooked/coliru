/* * * * * * * * * * * * *
 * M. Emery Goss         *
 * April 11, 2014        *
 *                       *
 * Time lambda inlining. *
 * * * * * * * * * * * * */


#include <algorithm>
#include <chrono>
#include <functional>
#include <iostream>
#include <string>


const int MAX_ITERATIONS = 10000;

template <typename F>
void run_test (std::string test_name, F block) {
    std::cout << test_name << std::endl;
    auto start = std::chrono::system_clock::now();
    for (int n = 0; n < MAX_ITERATIONS; ++n) block();
    auto end = std::chrono::system_clock::now();
    std::cout << "  time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl
              << std::endl;
}


int main () {

    auto control = [&]() {};

    run_test("control", [&]() {
        control();
    });

    int anchor = 0;
    auto raw = [&]() {
        for (int i = 0; i < 100000; ++i) {
            anchor += i;
        }
    };

    anchor = 0;
    run_test("raw", [&]() {
        raw();
    });
    std::cout << anchor << std::endl;

    anchor = 0;
    run_test("trivial lambda", [&]() {
        auto trivial_lambda = [&]() {
            raw();
        };

        trivial_lambda();
    });
    std::cout << anchor << std::endl;

    anchor = 0;
    run_test("argument passing lambda", [&]() {
        auto test_func = [&](std::function<void()> f) {
            f();
        };

        test_func(raw);
    });
    std::cout << anchor << std::endl;
}
