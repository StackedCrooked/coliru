#include <cstdlib>
#include <iostream>

//emulate MSVC's rand()
//this returns nonrandom results in the same
//range and distribution as MSVC's rand()
//as long as it's called a multiple of 32767 times;
int mrand() {
    static unsigned last=0;
    if (++last==32767)
        last = 0;
    return last;
}
#undef RAND_MAX
#define RAND_MAX 32767

int main() {
    const unsigned max = 1000;
    unsigned dist[max] = {};
    srand(time(NULL));
    for(unsigned i=0; i<32767*10000; ++i) {
        //int output = mrand()%max;
        int output = ((double)mrand()/(double)RAND_MAX)*max;
        dist[output] ++;
    }
    for (int i=0; i<max; ++i)
        std::cout << i << " : " << dist[i] << '\n';
}
