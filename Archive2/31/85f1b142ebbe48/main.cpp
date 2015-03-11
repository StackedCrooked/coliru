#include <chrono>
#include <future>
#include <iostream>
#include <thread>

bool is_prime(int x)
{
    for (int i = 2; i < x; ++i) {
        if ((x % i) == 0) {
            return false;
        }
    }
    return true;
}

unsigned count_primes()
{
    unsigned count = 0;
    for (int i = 2; i < 200000; ++i) {
        if (is_prime(i)) {
            ++count;
        }
    }
    return count;
}

int main()
{
    std::packaged_task<unsigned()> task{count_primes};
    auto f = task.get_future();
    std::thread t(std::move(task));

    if (f.wait_for(std::chrono::seconds(3)) == std::future_status::ready) {
        std::cout << "Primes count: " << f.get() << std::endl;
    } else {
        std::cout << "Timeout!\n";
    }

    return 0;
}
