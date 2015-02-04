#include "tbb/tbb.h"
#include <iomanip>
#include <iostream>
#include <thread>


long Fibonacci(long n)
{
    enum { CutOff = 10 };

    if (n < 2)
    {
        return n;
    }

    if (n < CutOff)
    {
        return Fibonacci(n - 1) + Fibonacci(n - 2);
    }

    struct FibTask: tbb::task
    {
        FibTask(long n, long& sum) : n(n), sum(&sum)
        {
        }

        tbb::task* execute()
        {

            if (n < CutOff)
            {
                *sum = Fibonacci(n);
                return nullptr;
            }

            struct Accumulate: tbb::task
            {
                Accumulate(long& sum) : sum(&sum), x(), y() {}

                tbb::task* execute()
                {
                    *sum = x + y;
                    return nullptr;
                }

                long* sum;
                long x, y;
            };


            auto& accumulator = *new (allocate_continuation()) Accumulate(*sum);

            // allocate a new task for Fib(n - 1)
            auto& fib_n_1 = *new (accumulator.allocate_child()) FibTask(n - 1, accumulator.x);

            // recycle "this" object for Fib(n - 2)
            auto& fib_n_2 = *this;
            fib_n_2.n = n - 2;
            fib_n_2.sum = &accumulator.y;
            fib_n_2.recycle_as_child_of(accumulator);

            // accumulator has two tasks
            accumulator.set_ref_count(2);

            // schedule Fib(n - 1) at the front of the queue
            spawn(fib_n_1);

            return &fib_n_2;
        }

        long n;
        long* sum;
    };


    long result = 0;
    auto& task = *new (tbb::task::allocate_root()) FibTask(n, result);
    tbb::task::spawn_root_and_wait(task);
    return result;
}


int main()
{
    for (int n = 0; n <= 50; ++n)
    {
        auto start_time = std::chrono::steady_clock::now();
        auto result = Fibonacci(n);
        auto elapsed_time = std::chrono::steady_clock::now() - start_time;

        std::cout << "n=" << std::setw(3) << std::left << n << " fib=" << std::setw(12) << std::left << result << " time=" << std::chrono::duration_cast<std::chrono::microseconds>(elapsed_time).count() / 1000.0 <<  "ms" << std::endl;
    }
}
