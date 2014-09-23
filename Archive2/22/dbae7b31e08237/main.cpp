#include <cassert>
#include <chrono>
#include <errno.h>
#include <time.h>

template <int Clock_ID>
struct posix_realtime_clock {
    using duration = std::chrono::nanoseconds;
    using rep = duration::rep;
    using period = duration::period;
    using time_point = std::chrono::time_point<posix_realtime_clock>;
    using clock = posix_realtime_clock;
    
    static constexpr bool is_steady{
        Clock_ID == CLOCK_MONOTONIC ||
        Clock_ID == CLOCK_MONOTONIC_COARSE ||
        Clock_ID == CLOCK_MONOTONIC_RAW ||
        Clock_ID == CLOCK_BOOTTIME
    };
    
    static time_point now() noexcept;
};

template <int Clock_ID>
auto posix_realtime_clock<Clock_ID>::now() noexcept -> time_point {
    struct timespec t;
    auto result = clock_gettime(Clock_ID, &t);
    assert(result != EINVAL);
    return time_point(std::chrono::seconds(t.tv_sec) + std::chrono::nanoseconds(t.tv_nsec));
}

using coarse_clock = posix_realtime_clock<CLOCK_MONOTONIC_COARSE>;

#include <iostream>
#include <unistd.h>

int main() {
    static const auto iterations = 10000000;
    auto start = coarse_clock::now();
    for (auto i = 0; i < iterations; ++i) {
        getpid();
    }
    auto stop = coarse_clock::now();
    std::cout << iterations << " calls to getpid took " << (stop - start).count() << " ns\n";
}
