#include <iostream>


using namespace std;


#pragma pack(push)
#pragma pack(1)
struct T0 {
    uint64_t aa;//8
    uint32_t bb;//4
    uint16_t cc;//2
    char dd;//1
};
#pragma pack(pop)

struct T1 {
    uint64_t aa;//8
    uint32_t bb;//4
    uint16_t cc;//2
    char dd;//1
};

//normal 16
//15 with pragma pack


int main() {
    cout << "size t0:" << sizeof(T0) << " size t1:" << sizeof(T1) << endl;
    return 0;
}
