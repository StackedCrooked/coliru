#include <deque>
#include <algorithm>
#include <functional>
#include <iostream>

template <typename F>
struct less_by_impl {
    less_by_impl(F&& f) : f(std::move(f)) { }
    template <typename T, typename U>
    bool operator()(T const& a, U const& b) const { return f(a) < f(b); }
    F f;
};

template <typename F>
less_by_impl<F> less_by(F&& f) { return less_by_impl<F>(std::forward<F>(f)); }

struct Entry {
    int nonUniqueInt;
    std::string somethingExtra;
};

using Container_t = std::deque<Entry>;

std::vector<Entry> const sampleData{
    {1, "first"}, {2, "second"}, {3, "third"}, {3, "fourth"}, {2, "fifth"}, {1, "sixth"}
};

int main() {
    Container_t lifo(sampleData.rbegin(), sampleData.rend()),
                fifo(sampleData.begin(), sampleData.end());

    auto cmp = less_by(std::mem_fn(&Entry::nonUniqueInt));

    for (Container_t& container: { ref(lifo), ref(fifo) })
    {
        std::stable_sort(container.begin(), container.end(), cmp);

        for(auto& entry : container)
            std::cout << entry.nonUniqueInt << ": " << entry.somethingExtra << "\n";

        std::cout << "\n";
    }
}
