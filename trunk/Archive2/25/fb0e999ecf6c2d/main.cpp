#include <ctime>
#include <bitset>
#include <iostream>

const int MAX = 128*8;
const int num_tests = 10000;

bool backet_test() {
    std::bitset<MAX> s;
    for(int j=0; j<num_tests; ++j) {
        for(int i=0; i<MAX; ++i)
            s[i] = !s[MAX-1-i];
    }
    return s[0];
}
bool set_test() {
    std::bitset<MAX> s;
    for(int j=0; j<num_tests; ++j) {
        for(int i=0; i<MAX; ++i)
            s.set(i, !s.test(MAX-1-i));
    }
    return s.test(0);
}

int main()
{
    clock_t t0,t1;
    bool r = false;
    
    t0 = clock();
    r = backet_test();
    t1 = clock();
    std::cout << "bracket_test: " << (t1 - t0) << " found " << r << std::endl;
    
    t0 = clock();
    r = set_test();
    t1 = clock();
    std::cout << "set_test: " << (t1 - t0) << " found " << r << std::endl;
}