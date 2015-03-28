#ifdef __linux__   
#include <iostream>
#include <sched.h> 
bool set_affinity (uint32_t mask) {
    return sched_setaffinity (0, sizeof mask, (cpu_set_t*)&mask) == 0;
}
uint32_t get_affinity () {
    uint32_t mask=0;
    sched_getaffinity (0, sizeof mask, (cpu_set_t*)&mask);
    return mask;
}
#elif _WIN32
#include <windows.h> 
#include <iostream>
bool set_affinity (DWORD mask) {
    return SetThreadAffinityMask (GetCurrentThread(), &mask);
}
unsigned get_current_proc_num () {
   int CPUInfo[4];   
   __cpuid(CPUInfo, 1);
   return (unsigned)CPUInfo[1] >> 24;
}

#endif

#include <thread>
#include <mutex>
#include <algorithm>
#include <vector>

std::mutex m;
void worker (unsigned name, unsigned mask) {
    std::lock_guard<std::mutex> lock(m);
    std::cout << "thread #" << name << "(" << mask << ")";
    if (!set_affinity (mask))
      std::cout << ": error set affinity\n";
    else
      std::cout << " is running with mask " << get_affinity () << std::endl;
}

int main()
{
    const size_t size=6;
    std::vector<std::thread> threads;
    for (size_t i=0; i != size; ++i) {
        threads.push_back (std::thread (&worker, i, 3*(i+1)));
    }
    std::for_each (threads.begin(), threads.end(), [](std::thread& t) {
        t.join();
    });
}