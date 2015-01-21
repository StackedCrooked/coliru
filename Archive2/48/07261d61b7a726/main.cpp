#include <algorithm>
#include <iostream>
#include <iterator>
#include <future>
#include <vector>

/* Minimum number of elements for multithreaded algorithm.
   Less than this and the algorithm is executed on single thread. */
static const int MT_MIN_SIZE = 10'000;

template <typename InputIt, typename T>
auto parallel_accumulate(InputIt first, InputIt last, T init) {
    // Determine total size.
    const auto size = std::distance(first, last);
    // Determine how many parts the work shall be split into.
    const auto parts = (size < MT_MIN_SIZE)? 1 : std::thread::hardware_concurrency();

    std::vector<std::future<T>> futures;

    // For each part, calculate size and run accumulate on a separate thread.
    for (std::size_t i = 0; i != parts; ++i) {
        const auto part_size = (size * i + size) / parts - (size * i) / parts;
        futures.emplace_back(std::async(std::launch::async,
            [=] { return std::accumulate(first, std::next(first, part_size), T{}); }));
        std::advance(first, part_size);
    }

    // Wait for all threads to finish execution and accumulate results.
    return std::accumulate(std::begin(futures), std::end(futures), init,
        [] (const T prev, auto& future) { return prev + future.get(); });
}

int main() {
    using namespace std::literals;

    std::vector<int> v(100'000'000, 0);
    std::iota(std::begin(v), std::end(v), 1);

    std::cout << "Sequential sum:" << std::endl;
    auto start = std::chrono::steady_clock::now();
    auto sum = std::accumulate(std::begin(v), std::end(v), 0ull);
    auto end = std::chrono::steady_clock::now();
    std::cout << "Time taken: " << std::chrono::duration_cast<decltype(1ms)>(end - start).count() << " ms" << std::endl;
    std::cout << "Sum: " << sum << std::endl;

    std::cout << "--------------------------------" << std::endl;

    std::cout << "Parallel sum:" << std::endl;
    start = std::chrono::steady_clock::now();
    sum = parallel_accumulate(std::begin(v), std::end(v), 0ull);
    end = std::chrono::steady_clock::now();
    std::cout << "Time taken: " << std::chrono::duration_cast<decltype(1ms)>(end - start).count() << " ms" << std::endl;
    std::cout << "Sum: " << sum << std::endl;
}