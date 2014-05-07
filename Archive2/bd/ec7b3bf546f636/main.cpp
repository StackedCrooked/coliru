#include <atomic>
#include <iostream>
#include <mutex>
#include <vector>
#include <thread>
#include <sstream>

std::mutex m1, m2, m3;

std::mutex print_mutex;

auto print = [](const std::string& s){
    std::lock_guard<std::mutex> lock_print_mutex(print_mutex);
    std::cout << s;
};

auto println = [](const std::string& s){
    print(s + '\n');
};

auto join = [](int i, int j, int k)
{
    std::stringstream ss;
    ss << i << ',' << j << ',' << k;
    return ss.str();
};



struct DeferLock : std::unique_lock<std::mutex> {
    DeferLock(std::mutex& m) : std::unique_lock<std::mutex>(m, std::defer_lock), fails() {}    
    
    bool try_lock() {
        if (!unique_lock::try_lock()) {
            fails++;
            return false;
        }
        return true;
    }
    
    int fails;
};

const int num_threads{6};
static std::atomic<int> num_started_threads;
static std::atomic<int> num_finished_threads;


auto lock_permute = [](int i, int j, int k) {   
    std::thread([=]{
        
        num_started_threads++;
        println("started permutation : " + join(i, j, k));
        while (num_started_threads != num_threads);
        
        DeferLock l1(m1), l2(m2), l3(m3);
        std::lock(l1, l2, l3);
        l1.unlock(), l2.unlock(), l3.unlock();    
        
        println("finished permutation: " + join(i, j, k) + " retries=" + join(l1.fails, l2.fails, l3.fails));
        num_finished_threads++;
    }).detach();
};


    
int main()
{
    lock_permute(0, 1, 2);
    lock_permute(0, 2, 1);
    lock_permute(1, 0, 2);
    lock_permute(1, 2, 0);
    lock_permute(2, 0, 1);
    lock_permute(2, 1, 0);
    
    while (num_finished_threads != num_threads);
}
