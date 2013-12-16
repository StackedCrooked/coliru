#include <atomic>
#include <iostream>
#include <mutex>
#include <thread>
#include <assert.h>
#include <unistd.h>
#include <stdint.h>


std::atomic<bool> lock{false};


void perform(uint32_t& fails, uint32_t& oks, uint32_t& total)
{    
    bool expected;
    do {        
        expected = false;
        lock.compare_exchange_weak(expected, true, std::memory_order_relaxed);
        if (expected) fails++;
    } while(expected);
    
    assert(lock == true);
    
    oks++;
    total++; // shared!
    
    lock.store(false, std::memory_order::memory_order_relaxed);
}


static const int iteration_count = 1000000;
std::atomic<int> started;



// prevent false sharing
static const int cache_line_size = 64 / sizeof(uint32_t);
uint32_t data[500]; 
uint32_t& reads       = data[0 * cache_line_size];
uint32_t& writes      = data[1 * cache_line_size];
uint32_t& total       = data[2 * cache_line_size];
uint32_t& write_fails = data[3 * cache_line_size];
uint32_t& read_fails  = data[4 * cache_line_size];


int main()
{
    std::thread([]{
        sleep(1);
        std::cout << "Deadlock!" << std::endl;
        std::abort();
    }).detach();
    
    std::thread writer_thread([]{
        
        started++;        
        while (started != 2);
        
        for (int i = 0; i != iteration_count; ++i)
        {
            perform(write_fails, writes, total);
        }
    });
    
    std::thread reader_thread([]{
        
        started++;        
        while (started != 2);
        
        for (int i = 0; i != iteration_count; ++i)
        {
            perform(read_fails, reads, total);
        }
    });
    
    
    writer_thread.join();
    reader_thread.join();
    
    std::cout << "reads :" << reads << ", failed: " << read_fails << " (" << int(0.5 + (100.0 * read_fails / reads)) << "%)" << std::endl;
    std::cout << "writes:" << writes << ", failed: " << write_fails << " (" << int(0.5 + (100.0 * write_fails / writes)) << "%)" << std::endl;
    std::cout << "total: " << total << std::endl;
}
