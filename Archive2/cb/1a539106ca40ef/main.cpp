constexpr unsigned long long fibo(unsigned n, unsigned long long prev = 1, unsigned long prevprev = 0) {
    return n == 0 ? prev : fibo(n - 1, prev + prevprev, prev);
}   

unsigned long long f(unsigned n) { return fibo(n); }
