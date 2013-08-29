#include <iostream>
#include <climits>
#include <iterator>

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

template<typename T>
void showMe() {
    T t;
    t.aa = 22ul;
    t.bb = INT_MAX;
    t.cc = 65000;
    t.dd = 'b';

    union T_test {
        T _t;
        uint8_t tab[sizeof(T)];
    };

    T_test tt;
    tt._t = t;

    std::cout << std::hex;
    for(auto el: tt.tab) {
        std::cout << (int)el << " ";  
    }
    std::cout << std::endl;
    std::cout << std::dec;
}


int main() {
    cout << "size t0:" << sizeof(T0) << " size t1:" << sizeof(T1) << endl;
    showMe<T0>();
    showMe<T1>();

    return 0;
}
