#ifdef __linux__   
#include <sched.h> 
bool set_affinity (unsigned long mask) {
    return sched_setaffinity (0, sizeof mask, (cpu_set_t*)&mask) == 0;
}
unsigned long get_affinity () {
    unsigned long mask=-1;
    return sched_getaffinity (0, sizeof mask, (cpu_set_t*)&mask)==0 ? mask : -1;
}
#elif _WIN32
#include <windows.h> 
bool set_affinity(DWORD mask) {
  return SetThreadAffinityMask(GetCurrentThread(), mask) != 0;
}
DWORD get_affinity() {
  DWORD mask = SetThreadAffinityMask(GetCurrentThread(), 1);
  SetThreadAffinityMask(GetCurrentThread(), mask);
  return mask != 0 ? mask : -1;
}
#endif

#include <iostream>
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
        threads.push_back (std::thread (&worker, i, 1<<i));
    }
    std::for_each (threads.begin(), threads.end(), [](std::thread& t) {
        t.join();
    });
}