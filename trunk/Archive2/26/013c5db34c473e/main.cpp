#include <thread>
#include <vector>

extern int library_function(bool);

static std::vector<std::thread> workers; // TODO implement a proper pool

void await_workers()
{
    for(auto& th: workers)
        if (th.joinable()) th.join();
}

template <typename F, typename C>
void do_with_continuation(F f, C continuation)
{
    workers.emplace_back([=] () mutable {
            auto result = f();
            continuation(result);
        });
}

#include <iostream>
#include <mutex>

void callback(int result)
{
    static std::mutex mx;
    std::lock_guard<std::mutex> lk(mx);
    std::cout << "Resulting value from callback " << result << "\n";
}

int main()
{
    // do something with delayed processing:
    do_with_continuation(std::bind(library_function, false), callback);
    do_with_continuation(std::bind(library_function, true),  callback);

    await_workers();
}

// somewhere, in another library:

#include <chrono>
int library_function(bool some_input)
{
    std::this_thread::sleep_for(std::chrono::seconds(some_input? 6 : 3));
    return some_input ? 42 : 0;
}

