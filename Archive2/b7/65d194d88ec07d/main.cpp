#include <chrono>
#include <cstdint>
#include <ratio>
#include <sstream>
#include <iostream>

class portable_system_clock {
public:
    using rep = std::int64_t;
    using period = std::micro;
    using duration = std::chrono::duration<rep, period>;
    using time_point = std::chrono::time_point<portable_system_clock>;

    static bool constexpr is_steady = std::chrono::system_clock::is_steady;

    static time_point now() {
        auto now = std::chrono::system_clock::now();
        return time_point(std::chrono::duration_cast<duration>(now.time_since_epoch()));
    }
};

int main() {
    auto const stored = portable_system_clock::now();

    std::stringstream os;
    auto const time = stored.time_since_epoch();

    os << time.count();

    std::int64_t us = -1;
    os >> us;

    portable_system_clock::time_point const loaded((portable_system_clock::duration(us)));

    std::cout << (stored == loaded);
}