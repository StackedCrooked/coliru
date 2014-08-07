#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

template<typename Integer = int>
class is_multiple_of {
public:
    is_multiple_of(Integer divisor) : divisor_{divisor} {}
    template<typename T> bool operator()(T i) { return i % divisor_ == 0; }
private:
    Integer divisor_;
};

#define N (3571)

int main() {
    std::vector<int> v(N - 1); // -1 because 1 is not prime
    std::iota(begin(v), end(v), 2);

    for (auto it = begin(v); it != end(v) && *it * *it <= N; ++it) {
        v.erase(std::remove_if(it + *it, end(v), is_multiple_of<>(*it)), end(v));
    }

    std::cout << "There are " << v.size() << " primes less than or equal to " << N << ".\n";
}