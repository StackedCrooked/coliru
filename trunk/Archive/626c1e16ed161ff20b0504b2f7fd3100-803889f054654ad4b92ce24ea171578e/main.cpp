#include <cstdlib>
#include <cassert>
#include <ctime>
#include <iostream>

int log2(unsigned v) {
    int r=0;
    while(v) {
        v/=2;
        ++r;
    }
    return r;
}

unsigned logrand() {
    unsigned topbit = 1<<(rand()%32);
    unsigned rest = rand()&(topbit-1);
    return topbit | rest;
}


int main() { 
    srand(time(NULL));
    unsigned block[33]  = {};
    const unsigned max = 1000000;
    for(unsigned i=0; i<max; ++i) {
        unsigned v = logrand();
        block[log2(v)]++;
    }
    std::cout << "bits\tcount\tpercent\n";
    for(int i=0; i<33; ++i)
        std::cout << i << '\t' << block[i] << '\t' << (block[i]*100.0/max) << "%\n";
}