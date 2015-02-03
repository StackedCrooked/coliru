#include <iostream>
#include <boost/chrono.hpp>
#include <boost/chrono/process_cpu_clocks.hpp>

using namespace boost::chrono;

template <typename R, typename P>
    static std::ostream& operator<<(std::ostream& os, duration<R,P> const& d) {
        return os << boost::chrono::duration_cast<boost::chrono::milliseconds>(d).count() << "ms";
    }

template <typename Clock = boost::chrono::process_cpu_clock, typename F, typename... Args>
nanoseconds bench(F&& f, Args&&... args) {
    auto start = Clock::now();

    volatile auto force = std::forward<F>(f)(std::forward<Args>(args)...);
    (void) force;

    return Clock::now() - start;
}

long long foo(int runs) {
    long long result = 0;
    for (int i = 0; i < runs; i++) {
        int x = rand() % 100 + 1;
        int y = rand() % 100 + 1;
        auto dummy = x * y;
        result = (result + dummy) % 50;
    }

    return result;
};

int main() {
    srand(time(NULL));

    std::cout << "1st method: " << bench(foo, 1e7)   << "\n";
    std::cout << "2nd method: " << bench(foo, 3e7) << "\n";
}
