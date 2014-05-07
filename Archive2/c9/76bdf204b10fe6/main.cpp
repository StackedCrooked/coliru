#include <atomic>
#include <iostream>
#include <mutex>
#include <vector>
#include <thread>

std::mutex m[3];
std::atomic<int> retries[3];

int get_index(std::mutex& mm) { return (&mm - m); }

struct Lock : std::unique_lock<std::mutex>
{
    Lock(std::mutex& m) : std::unique_lock<std::mutex>(m, std::defer_lock), n(get_index(m)) {}
    
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
    // 012, 021, 102, 120, 201, 210
    
    auto a = []{
        i++; while (i < 6); // wait until all threads have started
        Lock l0(m[0]), l1(m[1]), l2(m[2]); // is a defer lock
        std::lock(l0, l1, l2);                  // 012
        std::cout << __LINE__ << std::endl; // all locked -> safe to print
    };
    
    auto b = []{
        i++; while (i < 6);
        Lock l0(m[0]), l1(m[1]), l2(m[2]);    
        std::lock(l0, l2, l1);                  // 021
        std::cout << __LINE__ << std::endl;
    };
    
    auto c = []{
        i++; while (i < 6);
        Lock l0(m[0]), l1(m[1]), l2(m[2]);      
        std::lock(l1, l0, l2);                  // 102
        std::cout << __LINE__ << std::endl;
    };
    
    auto d = []{
        i++; while (i < 6);
        Lock l0(m[0]), l1(m[1]), l2(m[2]);
        std::lock(l1, l2, l0);                  // 120
        std::cout << __LINE__ << std::endl;
    };
    
    auto e = []{
        i++; while (i < 6);
        Lock l0(m[0]), l1(m[1]), l2(m[2]);       
        std::lock(l2, l0, l1);                  // 201
        std::cout << __LINE__ << std::endl;
    };
    
    auto f = []{
        i++; while (i < 6);
        Lock l0(m[0]), l1(m[1]), l2(m[2]);    
        std::lock(l2, l1, l0);                  // 210
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
