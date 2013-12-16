#include <cstdint>
#include <cstdio>

#define SWAP(A, B) do { decltype(auto) temp__ = (A); (A) = (B); (B) = temp__;  } while(0)

class RC4
{
    uint8_t state_[256];
    uint8_t i_;
    uint8_t j_;
public:
    
    RC4() : i_(0), j_(0) 
    {
        for(int i = 0; i < 256; ++i) state_[i] = i;
    }
    
    uint8_t operator()()
    {
        i_ += 1;
        j_ += state_[i_];
        SWAP(state_[i_], state_[j_]);
        return state_[255&(state_[i_] + state_[j_])];
    }
};


int main() 
{
    RC4 rc4;
    for(int i = 0; i < 1024*16; ++i)
        printf("%02X%s", rc4(), 63 == i % 64 ? "\n" : "");
    printf("\n");
    return 0;
}
