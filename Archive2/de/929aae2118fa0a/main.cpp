#include <cstdint>
#include <iostream>

using U64 = uint64_t;

// print bit indices of x
void setPrint(U64 x)
{
    std::cout << "{ ";
    for(auto i = 1; x; x >>= 1, ++i)
        if (x & 1) std::cout << i << ", ";
    std::cout << "}\n";
}

// get next greater subset of set with 
// Same Number Of One Bits
U64 snoob (U64 sub, U64 set) {
   U64 tmp = sub-1;
   U64 rip = set & (tmp + (sub & (0-sub)) - set);
   for(sub = (tmp & sub) ^ rip; sub &= sub-1; rip ^= tmp, set ^= tmp)
       tmp = set & (0-set);
   return rip;
}

void generatePowerSet(unsigned n)
{
    auto set = (1ULL << n) - 1;                 // n bits
    for (unsigned i = 0; i < n+1; ++i) {
        auto sub = (1ULL << i) - 1;             // i bits
        U64 x = sub; U64 y; 
        do {            
            setPrint(x);
            y = snoob(x, set);                  // get next subset
            x = y;
        } while ((y > sub));
    }
}

int main()
{
   generatePowerSet(4);    
}
