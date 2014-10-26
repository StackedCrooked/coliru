#include <utility>
#include <iostream>
#include <map>

bool coprime(unsigned m, unsigned n) {
    while (m) {
        n %= m;
        std::swap(m, n);
    }
    return n==1;
}

int main() {
    unsigned wins[1001] = {};
    for (unsigned a=2; a<1000; ++a)
        for (unsigned b=a+1; b<=1000; ++b)
            ++wins[(coprime(a,b) ? a : b)];

    std::multimap<unsigned, unsigned> sorted;
    for (unsigned n=2; n<=1000; ++n)
        sorted.insert(std::make_pair(wins[n], n));

    auto iter = sorted.crbegin();
    for (unsigned i=0; i<10; ++i, ++iter)
        std::cout << iter->second << " (" << iter->first << "/999)\n";
}
