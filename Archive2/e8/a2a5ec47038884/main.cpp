#include <iostream>
#include <algorithm>
#include <atomic>
#include <thread>
#include <vector>

void foo(std::atomic_int& aval, int& val)
{
    for (int i=0;i<1000000;++i,++aval,++val);
}

int main(int argc, char *argv[])
{
    std::vector<std::thread> thrds;
    std::atomic_int a_int = ATOMIC_VAR_INIT(0);
    int raw_int = 0;
    
    unsigned int N = std::thread::hardware_concurrency()+1;
    std::cout << "Using " << N << " threads..." << std::endl;
    std::generate_n(std::back_inserter(thrds), N,
        [&](){return std::thread(foo, std::ref(a_int), std::ref(raw_int));});
    
    std::for_each(thrds.begin(), thrds.end(), [](std::thread& t){ t.join(); });
    
    std::cout << "Non-Atomic: " << raw_int << std::endl;
    std::cout << "Atomic:     " << a_int << std::endl;
    return 0;
}