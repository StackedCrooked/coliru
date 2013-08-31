#include <algorithm>
#include <vector>
#include <stdio.h>


enum {
    FIN = 1 << 0,
    SYN = 1 << 1,
    ACK = 1 << 2,
    RST = 1 << 3,
    FlagCount = 1 << 4
};


// handy for printing integer as binary
const char binary4[16][sizeof("xxxx")] = {
    "0000",  "0001",  "0010",  "0011",
    "0100",  "0101",  "0110",  "0111", 
    "1000",  "1001",  "1010",  "1011",
    "1100",  "1101",  "1110",  "1111"
};

void test()
{
    typedef void(*Validator)();
    
    // Define the lookup table
    Validator lookup_table[FlagCount];
    
    // Assign the default validator to each.
    using std::begin;
    using std::end;
    std::fill(begin(lookup_table), end(lookup_table), []{ printf("invalid bitmask"); });
    
    // Overwrite entries which are valid.
    lookup_table[0] = []{ printf("no flags"); };
    lookup_table[SYN] = []{ printf("SYN"); };
    lookup_table[FIN] = []{ printf("FIN"); };
    lookup_table[ACK] = []{ printf("ACK"); };    
    lookup_table[SYN|ACK] = []{ printf("SYN|ACK"); };
    lookup_table[FIN|ACK] = []{ printf("FIN|ACK"); };
    lookup_table[RST] = []{ printf("RST"); };
    
    // Test all entries.
    unsigned index = 0;
    for (auto&& f : lookup_table)
    {
        printf("\n%s\t", binary4[index++]);
        f();
    }
}

int main()
{    
    test();    
}