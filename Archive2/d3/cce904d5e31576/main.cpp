#include <thread>
#include <future>
#include <iostream>
#include <vector>
#include <algorithm>

bool odd(int i) { return i & 1; }

template <typename R, typename OutIt>
void exec_and_collect(OutIt results, std::vector<std::function<R()> > const &tasks) {
    std::vector<std::future<R> > futures;

    auto my_async = [](std::function<R()> const &t) {
        std::packaged_task<R()> task(std::forward<decltype(t)>(t));
        auto future = task.get_future();
        std::thread(std::move(task)).detach();
        return future;
    };

    std::transform(tasks.begin(), tasks.end(), std::back_inserter(futures), my_async);
    std::transform(futures.begin(), futures.end(), results, std::mem_fn(&std::future<R>::get));
}

#include <boost/range/irange.hpp>
#include <boost/range/adaptors.hpp>

using namespace boost::adaptors;

int main() {
    std::vector<bool> results;
    std::vector<std::function<bool()> > tasks;

    for (int i = 0; i < 8; ++i) {
        tasks.emplace_back(std::bind(odd, i));
    }

    exec_and_collect(std::back_inserter(results), tasks);

    for (bool b : results)
        std::cout << std::boolalpha << b << "; ";
}
