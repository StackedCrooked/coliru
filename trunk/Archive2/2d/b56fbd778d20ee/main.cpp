#include <thread>
#include <future>
#include <iostream>
#include <vector>
#include <algorithm>

#include <boost/range.hpp>

bool odd(int i) { return (((i&1)==1)?true:false); }

template <typename Range, typename OutIt>
void exec_and_collect(OutIt results, Range&& tasks) {
    using namespace std;
    using T = typename boost::range_value<Range>::type;
    using R = decltype(declval<T>()());

    auto tb = std::make_move_iterator(boost::begin(tasks)),
         te = std::make_move_iterator(boost::end(tasks));

    vector<future<R>> futures;

    transform(
            tb, te,
            back_inserter(futures), [](auto&& t) {
                std::packaged_task<R()> task(std::forward<decltype(t)>(t));
                auto future = task.get_future();
                thread(std::move(task)).detach();
                return future;
            });

    // threads are now running, collect results
    transform(begin(futures), end(futures), results, [](auto& fut) { return fut.get(); });
}

#include <boost/range/irange.hpp>
#include <boost/range/adaptors.hpp>

using namespace boost::adaptors;

int main() {
    std::vector<bool> results;
    exec_and_collect(
            std::back_inserter(results), 
            boost::irange(0, 8) | transformed([](int i) { return [i] { return odd(i); }; })
        );

    std::copy(results.begin(), results.end(), std::ostream_iterator<bool>(std::cout << std::boolalpha, "; "));
}
