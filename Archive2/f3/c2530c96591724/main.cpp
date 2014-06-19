// future example
#include <iostream>       // std::cout
#include <future>         // std::async, std::future
#include <chrono>         // std::chrono::milliseconds


const int number = 4; // 444444443

// a non-optimized way of checking for prime numbers:
bool is_prime (int x)
{
    for (int i = 2; i < x; ++i) if (x % i == 0) return false;
    return true;
}

int main ()
{
    // call function asynchronously:
    std::future<bool> fut = std::async (/*std::launch::async,*/ is_prime, number);

    // do something while waiting for function to set future:
    std::cout << "checking, please wait";
    std::chrono::milliseconds span (100);
    //std::chrono::duration<int> span (1);

    while (fut.wait_for(span) == std::future_status::timeout) {
        std::cout << '.';
        std::cout.flush();
    }


    bool x = fut.get();     // retrieve return value

    std::cout << "\n" << number << " " << (x ? "is" : "is not") << " prime.\n";

    return 0;
}
