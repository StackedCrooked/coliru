#include <iostream>
using namespace std;
#include <x86intrin.h>
#include <stdint.h>

int main(){
    char flag = 0;

    uint64_t a = 123;
    uint64_t b = 123;

    flag = _addcarry_u64(flag,a,b,&a);
    flag = _addcarry_u64(flag,a,b,&a);

}

