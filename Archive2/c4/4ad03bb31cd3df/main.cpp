#include <cassert>
#include <chrono>
#include <errno.h>
#include <iostream>
#include <time.h>

class fast_monotonic_clock {
public:
    using duration = std::chrono::nanoseconds;
    using rep = duration::rep;
    using period = duration::period;
    using time_point = std::chrono::time_point<fast_monotonic_clock>;
    
    static constexpr bool is_steady = true;
    
    static time_point now() noexcept;
    
    static duration get_resolution() noexcept;

private:
    static clockid_t clock_id();
    static clockid_t test_coarse_clock();
    static duration convert(const timespec&);
};

inline clockid_t fast_monotonic_clock::test_coarse_clock() {
    struct timespec t;
    if (clock_gettime(CLOCK_MONOTONIC_COARSE, &t) == 0) {
        std::cout << "System has CLOCK_MONOTONIC_COARSE\n";
        return CLOCK_MONOTONIC_COARSE;
    } else {
        std::cout << "System doesn't have CLOCK_MONOTONIC_COARSE\n";
        return CLOCK_MONOTONIC;
    }
}

clockid_t fast_monotonic_clock::clock_id() {
    static clockid_t the_clock = test_coarse_clock();
    return the_clock;
}

inline auto fast_monotonic_clock::convert(const timespec& t) -> duration {
    return std::chrono::seconds(t.tv_sec) + std::chrono::nanoseconds(t.tv_nsec);
}

auto fast_monotonic_clock::now() noexcept -> time_point {
    struct timespec t;
    const auto result = clock_gettime(clock_id(), &t);
    assert(result == 0);
    return time_point{convert(t)};
}

auto fast_monotonic_clock::get_resolution() noexcept -> duration {
    struct timespec t;
    const auto result = clock_getres(clock_id(), &t);
    assert(result == 0);
    return convert(t);
}

#include <unistd.h>

int main() {
    const auto resolution = fast_monotonic_clock::get_resolution().count();
    std::cout << "clock resolution is " << resolution << " ns\n";
    
    static const auto iterations = 10000000;
    auto check_start = std::chrono::steady_clock::now();
    auto start = fast_monotonic_clock::now();
    for (auto i = 0; i < iterations; ++i) {
        getpid();
    }
    auto check_stop = std::chrono::steady_clock::now();
    auto stop = fast_monotonic_clock::now();
    std::cout << iterations << " calls to getpid took " << (stop - start).count() << " ns, "
              << std::chrono::nanoseconds(check_stop - check_start).count() << " ns according to steady_clock.\n";
}
