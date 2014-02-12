#include <iostream>
#include <algorithm>


using namespace std;

__inline__ uint64_t rdtsc() {
  uint64_t a, d;
  __asm__ volatile ("rdtsc" : "=a" (a), "=d" (d));
  return (d<<32) | a;
}

class mytimer
{
 public:
  mytimer() { _start_time = rdtsc(); }
  void   restart() { _start_time = rdtsc(); }
  uint64_t elapsed() const
  { return  rdtsc() - _start_time; }

 private:
  uint64_t _start_time;
}; // timer

int main()
{
    const int num_samples = 1000000;
    float* samples = new float[num_samples];
    mytimer timer;
    for (int i = 0; i < num_samples; i++) {
        samples[i] = 1.f;
    }
    unsigned long long result = timer.elapsed();
    std::cout << "rewrite of " << (static_cast<double>(num_samples)*sizeof(float)/(1024.*1024)) 
              << " Mb takes " << result << std::endl;

    timer.restart();
    float sum = 0;
    for (int i = 0; i < num_samples; i++) {
        sum += samples[i];
    }
    result = timer.elapsed();
    std::cout << "naive:\t\t" << result << ", sum = " << sum << std::endl;

    timer.restart();
    float* end = samples + num_samples;
    sum = 0;
    for(float* i = samples; i < end; i++) {
        sum += *i;
    }
    result = timer.elapsed();
    std::cout << "pointers:\t" << result << ", sum = " << sum << std::endl;

    timer.restart();
    sum = 0;
    sum = std::accumulate(samples, end, 0.f);
    result = timer.elapsed();
    std::cout << "algorithm:\t" << result << ", sum = " << sum << std::endl;

    // With ILP
    timer.restart();
    float sum0 = 0, sum1 = 0;
    sum = 0;
    for (int i = 0; i < num_samples; i+=2) {
        sum0 += samples[i];
        sum1 += samples[i+1];
    }
    sum = sum0 + sum1;
    result = timer.elapsed();
    std::cout << "ILP:\t\t" << result << ", sum = " << sum << std::endl;
}
