#include <iostream>
#include <vector>
#include <numeric>
#include <chrono>

class thousands : public std::numpunct<decltype(std::cout)::char_type> {
    private:
    std::string do_grouping() const override final { return "\3"; }
};

//using my_clock = std::chrono::high_resolution_clock;
using my_clock = std::chrono::system_clock;
//using my_clock = std::chrono::steady_clock;

template <typename clock_type>
auto ticks_per_second() { return typename clock_type::duration{std::chrono::seconds{1}}.count(); }

volatile int sink;
int main()
{
    std::cout.imbue(std::locale(std::cout.getloc(), new thousands));
    std::cout << "One second is " << ticks_per_second<my_clock>() << " ticks\n";
    for (unsigned long long size = 1; size <= 100'000'000ull; size *= 10) {
        // record start time
        auto start = my_clock::now();
        // do some work
        std::vector<int> v(size, 42);
        sink = std::accumulate(v.begin(), v.end(), 0u); // make sure it's a side effect
        // record end time
        auto end = my_clock::now();
        my_clock::duration diff = end-start;
        std::cout << "Time to fill and iterate a vector of " 
                  << size << " ints : " << diff.count() << " ticks\n";
    }
}