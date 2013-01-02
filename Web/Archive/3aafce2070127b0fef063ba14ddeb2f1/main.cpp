#include <iostream>
#include <chrono>

using ullong = unsigned long long;
class Stopwatch {
public:
    typedef std::chrono::high_resolution_clock Clock;
    Clock::time_point start;
    Stopwatch(): start(Clock::now()) {}
    void elapsed() {
        std::cout << "Elapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now()-start).count() << " ms\n";
    }
};

inline ullong triangle(ullong n) {
    return n*(n+1)/2;
}

ullong counter(ullong n) {
    ullong result = 0;
    for(ullong i = 1; i*i <= n; ++i) {
        if(n % i == 0) {
            result += 2;
            if(n / i == i)
                --result;
        }
    }
    return result;
}

ullong factors(ullong n) {
    ullong k = 0;
    for(ullong i = 1; k <= n; ++i) {
        if(i % 2 == 0)
            k = counter(i/2)*counter(i+1);
        else
            k = counter(i) * counter((i+1)/2);
        if(k > 500) {
            return i;
        }
    }
    return 0;
}

int main() {
    Stopwatch k;
    ullong i = factors(500);
    std::cout << triangle(i) << '\n';
    k.elapsed();
}