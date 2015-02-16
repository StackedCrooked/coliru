#include <iostream>
#include <boost/container/flat_map.hpp>
#include <chrono>
using namespace std;

using Map = boost::container::flat_map<string, int>;

int get(Map &e, char *s) { return e[s]; }
int set(Map &e, char *s, int value) { return e[s] = value; }

using Clock = std::chrono::high_resolution_clock;

template <typename F, typename Reso = std::chrono::microseconds, typename... Args> 
Reso measure(F&& f, Args&&... args) {
    auto since = Clock::now();
    std::forward<F>(f)(std::forward<Args>(args)...);
    return chrono::duration_cast<Reso>(Clock::now() - since);
}

#include <boost/iterator/iterator_facade.hpp>

using Pair = std::pair<std::string, int>;

struct Gen : boost::iterators::iterator_facade<Gen, Pair, boost::iterators::single_pass_traversal_tag, Pair>
{
    int i;
    Gen(int i = 0) : i(i) {}

    value_type dereference() const { 
        char buf[10];
        std::sprintf(buf, "%08d", i);
        return { buf, i%1000 }; 
    }
    bool equal(Gen const& o) const { return i==o.i; }
    void increment() { ++i; }
};

int main() {
    Map Employees;
    const auto n = 1000000;

    auto elapsed = measure([&] {
            Employees.reserve(n);
            Employees.insert<Gen>(boost::container::ordered_unique_range, {0}, {n});
        });

    std::cout << "took " << elapsed.count() / 1000000.0 << " sec\n";

    cout << Employees["00001234"] << endl;
}
