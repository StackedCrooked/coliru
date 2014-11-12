#include <thread>
#include <atomic>
#include <chrono>
#include <iostream>





void test(int i, int j, int k)
{
    alignas(128) std::atomic<uint64_t> n[100] = {};
    std::atomic<uint64_t>& flag = n[99];

    std::thread t1([&]{ flag++; while (flag != 4) continue; while (flag == 4) n[i]++; });
    std::thread t2([&]{ flag++; while (flag != 4) continue; while (flag == 4) n[j]++; });
    std::thread t3([&]{ flag++; while (flag != 4) continue; while (flag == 4) n[k]++; });

    // wait until threads are ready to run
    while (flag != 3);

    // unleash the threads
    flag++;

    // let the go for a while
    std::this_thread::sleep_for(std::chrono::microseconds(10000));

    // stop threads
    flag++;
    t1.join(), t2.join(), t3.join();

    std::cout << n[i]/10000 << ' '
              << n[j]/10000 << ' '
              << n[k]/10000 << "\n";
}


int main()
{
    test(30, 31, 32);
}

