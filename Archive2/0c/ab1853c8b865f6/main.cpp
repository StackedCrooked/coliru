#include <iostream>
#include <string>
#include <mutex>
#include <omp.h>
 
thread_local unsigned int rage = 1; 
std::mutex cout_mutex;
 
void increase_rage(const std::string& thread_name)
{
    ++rage;
    std::lock_guard<std::mutex> lock(cout_mutex);
    std::cout << "Rage counter for " << thread_name << ": " << rage << '\n';
}
 
int main()
{
    const char* v[] = { "а", "б", "в", "г" };
    
    #pragma omp parallel
    {    
        increase_rage(v[omp_get_thread_num()]);
    }
    return 0;
}