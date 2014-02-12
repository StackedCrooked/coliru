#include <bitset>
#include <algorithm>
#include <iostream>

const int MAX = 128*8;
const int num_iterations = 1000;
const int num_tests = 10;

inline uint64_t RDTSC()
{
    uint32_t a;
    uint32_t d;
    asm volatile
        (".byte 0x0f, 0x31 #rdtsc\n" // edx:eax
         :"=a"(a), "=d"(d)::);
    return (((uint64_t) d) << 32) | (uint64_t) a;
}

bool bracket_test() {
    std::bitset<MAX> s;
    for(int j=0; j<num_iterations; ++j) {
        for(int i=0; i<MAX; ++i)
            s[i] = !s[MAX-1-i];
    }
    return s[0];
}
bool set_test() {
    std::bitset<MAX> s;
    for(int j=0; j<num_iterations; ++j) {
        for(int i=0; i<MAX; ++i)
            s.set(i, !s.test(MAX-1-i));
    }
    return s.test(0);
}
bool no_test() {
    bool s = false;
    for(int j=0; j<num_iterations; ++j) {
        for(int i=0; i<MAX; ++i)
            s = !s;
    }
    return s;
}

void do_test_set(bool (*func)(), const char* name) {
    uint64_t t0;
    uint64_t timings[num_tests] = {0};
    bool r = false;
    for(int i=0; i<num_tests; ++i) {
        t0 = RDTSC();
        r = func();
        timings[i] = RDTSC()-t0;
    }
    uint64_t min = *std::min(timings+0, timings+num_tests);
    std::cout << name << " took " << min << " ticks to find result " << r << '\n';
}

int main()
{
    do_test_set(bracket_test, "bracket_test");
    do_test_set(set_test,     "set_test    ");
    do_test_set(no_test,      "no_test     ");
}