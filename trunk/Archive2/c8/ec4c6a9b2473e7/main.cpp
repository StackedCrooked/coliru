#include <atomic>
#include <iostream>
#include <mutex>
#include <vector>
#include <thread>

std::mutex mutexes[3];
std::atomic<int> retries[3];
auto& m1 = mutexes[0];
auto& m2 = mutexes[1];
auto& m3 = mutexes[2];

struct Lock : std::unique_lock<std::mutex>
{
    Lock(std::mutex& m) : std::unique_lock<std::mutex>(m, std::defer_lock), n(1 + (&m - &m1)) {}
    
    bool try_lock()
    {
        if (!unique_lock::try_lock())
        {
            retries[n]++;
            return false;
        }
        else
        {
            std::cout << "Locked " << n << " after " << retries[n] << " retries\n";
            return true;
        }
    }
    
    int n;
};


std::atomic<int> i{0}; // number of started threads

    
int main()
{
    // all possible lock orderings:
    // 123, 132, 213, 231, 312, 321
    
    
    auto a = []{
        i++; while (i < 6);
        Lock l1(m1), l2(m2), l3(m3);    
        std::lock(l1, l2, l3);
        std::cout << __LINE__ << std::endl;
    };
    
    auto b = []{
        i++; while (i < 6);
        Lock l1(m1), l2(m2), l3(m3);    
        std::lock(l1, l3, l2);
        std::cout << __LINE__ << std::endl;
    };
    
    auto c = []{
        i++; while (i < 6);
        Lock l1(m1), l2(m2), l3(m3);      
        std::lock(l2, l1, l3);
        std::cout << __LINE__ << std::endl;
    };
    
    auto d = []{
        i++; while (i < 6);
        Lock l1(m1), l2(m2), l3(m3);      
        std::lock(l2, l3, l1);
        std::cout << __LINE__ << std::endl;
    };
    
    auto e = []{
        i++; while (i < 6);
        Lock l1(m1), l2(m2), l3(m3);       
        std::lock(l3, l1, l2);
        std::cout << __LINE__ << std::endl;
    };
    
    auto f = []{
        i++; while (i < 6);
        Lock l1(m1), l2(m2), l3(m3);    
        std::lock(l3, l2, l1);
        std::cout << __LINE__ << std::endl;
    };
    
    std::vector<std::thread> threads;
    threads.reserve(6);
    threads.emplace_back(a);
    threads.emplace_back(b);
    threads.emplace_back(c);
    threads.emplace_back(d);
    threads.emplace_back(e);
    threads.emplace_back(f);
    
    for (auto&& t : threads) t.join();
    
    std::cout << "Done" << std::endl;
}
