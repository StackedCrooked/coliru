#include <iostream>
#include <ctime>
#include <cstdlib>
#include <boost/chrono.hpp>
#include <boost/chrono/process_cpu_clocks.hpp>

using namespace boost::chrono;

template <typename R, typename P>
    static std::ostream& operator<<(std::ostream& os, duration<R,P> const& d) {
        return os << duration_cast<milliseconds>(d).count() << "ms";
    }

template <typename F, typename... Args>
nanoseconds bench(F&& f, Args&&... args) {
    auto start = high_resolution_clock::now();

    volatile auto force = std::forward<F>(f)(std::forward<Args>(args)...);
    (void) force;

    return high_resolution_clock::now() - start;
}

int main() {
    srand(time(NULL));

    auto ll = [](int runs) {
        long long result = 0;
        for (int i = 0; i < runs; i++) {
            int x = rand() % 100 + 1;
            int y = rand() % 100 + 1;
            auto dummy = x * y;
            result = (result + dummy) % 50;
        }
    
        return result;
    };

    std::cout << "1st method: " << bench(ll, 1e7)   << "\n";
    std::cout << "2nd method: " << bench(ll, 3e7) << "\n";
}
