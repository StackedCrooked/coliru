#include <iostream>
#include <iomanip>
#include <climits>

static inline unsigned long long rdtsc()
{
  unsigned hi, lo;
  __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
  return ( (unsigned long long)lo)|( ((unsigned long long)hi)<<32 );
}

inline bool noop(unsigned int x)
{return x;}

inline bool modulo15(unsigned int x)
{return x%15==0;}

inline bool divisible15(unsigned int x)  //for optimal result use this as a inline
{return x * 4008636143u <= 286331153u;}

void accuracy() {
    for(unsigned i=0; i<46; ++i) {
        if (divisible15(i) != modulo15(i))
            std::cerr << "wrong answer for " << i << '\n';
    }
    for(unsigned i=UINT_MAX; i>UINT_MAX-46; --i) {
        if (divisible15(i) != modulo15(i))
            std::cerr << "wrong answer for " << i << '\n';
    }
}

template<bool(&func)(unsigned int)>
void time(const char* name) {
    unsigned sum = 0;
    unsigned long long begin = rdtsc();
    for(unsigned i=0; i<100000000; ++i)
        sum += func(i);
    unsigned long long end = rdtsc();
    std::cout<<std::setw(11)<<name<<" found "<<std::setw(8)<<sum<<" in "<<std::setw(9)<<(end-begin)<<" ticks.\n";
}

int main(int argc, char* argv[])
{
    accuracy();
    time<noop>("noop");
    time<noop>("noop");
    time<noop>("noop");
    time<modulo15>("modulo15");
    time<modulo15>("modulo15");
    time<modulo15>("modulo15");
    time<divisible15>("divisible15");
    time<divisible15>("divisible15");
    time<divisible15>("divisible15");
    time<modulo15>("modulo15");
    time<modulo15>("modulo15");
    time<modulo15>("modulo15");
    time<noop>("noop");
    time<noop>("noop");
    time<noop>("noop");
    time<divisible15>("divisible15");
    time<divisible15>("divisible15");
    time<divisible15>("divisible15");
    time<noop>("noop");
    time<noop>("noop");
    time<noop>("noop");
    return 0;
}