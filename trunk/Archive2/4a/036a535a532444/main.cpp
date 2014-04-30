#include <future>
#include <chrono>
#include <thread>
#include <iostream>

int
main()
{
    auto s = [](int n) {
        std::this_thread::sleep_for(std::chrono::seconds(n));
        std::cout << "slept for " << n << " sec., thread id #" << std::this_thread::get_id() << std::endl;
        return n;
    };

    std::packaged_task<int(int)> task1(s);
    std::packaged_task<int(int)> task2(s);

    auto r1 = task1.get_future();
    std::thread t1(std::move(task1), 1);
    t1.detach();
    std::cout << "1-st thread detached" << std::endl;

    auto r2 = task2.get_future();
    std::thread t2(std::move(task2), 2);
    t2.detach();
    std::cout << "2-nd thread detached" << std::endl;

    std::cout << "main thread id #" << std::this_thread::get_id() << std::endl; 

    // here we are waiting for the result
    std::cout << r1.get() << std::endl;
    std::cout << r2.get() << std::endl;

    return 0;
}
