#include <string>
#include <thread>
#include <vector>
#include <iostream>
#include <atomic>
#include <chrono>
 
// meaning of cnt:
// 10: there are no active readers or writers.
// 1...9: there are 9...1 readers active, The writer is blocked
// 0: temporary value between fetch_sub and fetch_add in reader lock
// -1: there is a writer active. The readers are blocked.
const int N = 10; // nine concurrent readers are allowed
std::atomic<int> cnt = ATOMIC_VAR_INIT(N);
 
std::vector<int> data;
 
void reader(int id)
{
    for(;;)
    {
        // lock
        while(std::atomic_fetch_sub(&cnt, 1) <= 0)
            std::atomic_fetch_add(&cnt, 1);
        // read
        if(!data.empty())
            std::cout << (  "reader " + std::to_string(id)
                          + " sees " + std::to_string(*data.rbegin()) + '\n');
        if(data.size() == 100)
            break;
        // unlock
        std::atomic_fetch_add(&cnt, 1);
        // pause
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}
 
void writer()
{
    for(int n = 0; n < 100; ++n)
    {
        // lock
        while(std::atomic_fetch_sub(&cnt, N+1) != N)
            std::atomic_fetch_add(&cnt, N+1);
        // write
        data.push_back(n);
        std::cout << "writer pushed back " << n << '\n';
        // unlock
        std::atomic_fetch_add(&cnt, N+1);
        // pause
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}
 
int main()
{
    std::vector<std::thread> v;
    for (int n = 0; n < N; ++n) {
        v.emplace_back(reader, n);
    }
    v.emplace_back(writer);
    for (auto& t : v) {
        t.join();
    }
}