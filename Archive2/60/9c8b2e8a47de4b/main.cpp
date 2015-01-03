//http://stackoverflow.com/questions/27759118/int-to-float-with-bitwise-operators-in-c
#include <stdio.h>
#include <stdint.h>

typedef union{
    uint32_t x;
    float fx;
}df;

unsigned find_e(int32_t x,unsigned i){
    if(x&(1<<i)) return i;
    if(x==0) return -127;
    return find_e(x,--i);
}
float int_to_float(int x){
    df ime;
    ime.x=0;
    unsigned sign = 0;
    if(x<0){x=-x;sign = 1<<31; }
    unsigned position = find_e(x,31);
    unsigned e = position + 127;
    uint32_t m = (x&(~(~0<<position)))<<(32-position);
    ime.x |= sign;
    ime.x |= e<<23;
    ime.x |= m>>9;
    return ime.fx;
}

int main()
{
    int input[] = { 0, 2, 19, 43, 7, 6, 13, 58, -2, -19, -43, -7, -6, -13, -58 };
    size_t const N = sizeof(input) / sizeof(input[0]);
    unsigned i;
    for(i=0; i<N; ++i) {
        int x = input[i];
        printf("%d %f\n", x, int_to_float(x));
    }
    return 0;
}