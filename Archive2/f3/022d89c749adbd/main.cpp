#include <atomic>

template <typename kind = void, typename id = long long>
id unique_id ( ) {
    static std::atomic<long long> generator;
    return generator++;
}

#include <iostream>
#include <vector>
#include <thread>

void dump_id () {    
    std::cout << "From Thread (" << std::this_thread::get_id() << "): " << unique_id<>() << std::endl;
}

int main()
{
    std::cout << "Starting..." << std::endl;
    
    std::vector<std::thread> threads;
    threads.reserve(8);
    
    std::cout << "Main Thread (" << std::this_thread::get_id() << "): " << unique_id<>() << std::endl;
    for (std::size_t i = 0; i < 8; ++i) {
        threads.push_back( std::thread( dump_id ) );
    }
    
    std::cout << "Main Thread (" << std::this_thread::get_id() << "): " << unique_id<>() << std::endl;
    std::cout << "Main Thread (" << std::this_thread::get_id() << "): " << unique_id<>() << std::endl;
    
    for ( auto& thread : threads )
        thread.join();
        
    std::cout << "Terminating..." << std::endl;
}
