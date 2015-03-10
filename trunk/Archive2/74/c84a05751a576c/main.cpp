/* * * * * * * * * * * * * *
 * M. Emery Goss           *
 * February 17, 2015       *
 *                         *
 * Time continue vs.       *
 *  nested if statements.  *
 * * * * * * * * * * * * * */

#include <chrono>
#include <functional>
#include <iostream>
#include <string>


const int MAX_TRIALS = 10000;
const int MAX_ITERATIONS = 10000;

template <typename F>
void run_test (std::string test_name, F block) {
    std::cout << test_name << std::endl;
    auto start = std::chrono::system_clock::now();
    for (int n = 0; n < MAX_TRIALS; ++n) block();
    auto end = std::chrono::system_clock::now();
    std::cout << "  time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl
              << std::endl;
}


int main () {
    run_test("control", []() {
        int sum = 0;
        for (int i = 0; i < MAX_ITERATIONS; ++i) {
        }
    });

    run_test("continue", []() {
        int sum = 0;
        for (int i = 0; i < MAX_ITERATIONS; ++i) {
            if (i % 2) {
                continue;
            }
            
            sum += i;
        }
    });
    
    run_test("nested-if", []() {
        int sum = 0;
        for (int i = 0; i < MAX_ITERATIONS; ++i) {
            if (not (i % 2))
                sum =+ i;
        }
    });

    return 0;
}
