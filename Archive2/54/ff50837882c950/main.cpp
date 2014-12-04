int multiply_compare(int left1, int left2, int right1, int right2) {
    //find high 32 bits (sans all carries)
    int lefthigh = (left1>>16) * (left2>>16);
    int righthigh = (right1>>16) * (right2>>16);
    
    //OPTIONAL: compare highest 16 bits accounting for possible carry bit
    if ((lefthigh>>16) + 1 < (righthigh>>16))
        return -1;
    if ((lefthigh>>16) > (righthigh>>16) + 1)
        return 1;
    
    //find middle 32 bits (sans all carries)
    int leftmid1 = (left1&0xFFFF) * (left2>>16);
    int leftmid2 = (left1>>16) * (left2&0xFFFF);
    int rightmid1 = (right1&0xFFFF) * (right2>>16);
    int rightmid2 = (right1>>16) * (right2&0xFFFF);
    
    //bring in most carries from middle to high (there's still one possible carry bit)
    lefthigh += (leftmid1>>16) + (leftmid2>>16);
    righthigh += (rightmid1>>16) + (rightmid2>>16);
    
    //OPTIONAL: compare highest 32 accounting for possible carry bit
    if (lefthigh + 1 < righthigh)
        return -1;
    if (lefthigh > righthigh + 1)
        return 1;
        
    //remove bits from mid that carried to high already, and finalize middle 32 bits (sans carries)
    leftmid1 = (leftmid1&0xFFFF) + (leftmid2&0xFFFF);
    rightmid1 = (rightmid1&0xFFFF) + (rightmid2&0xFFFF);
        
    //calculate low bits
    int leftlow = (left1&0xFFFF) * (left2&0xFFFF);
    int rightlow = (right1&0xFFFF) * (right2&0xFFFF);
    
    //finalize all carries
    leftmid1 += (leftlow>>16);
    rightmid1 += (rightlow>>16);
    lefthigh += (leftmid1>>16);
    righthigh += (rightmid1>>16);
    
    //compare highest to lowest
    if (lefthigh<righthigh) return -1;
    if (lefthigh>righthigh) return 1;
    if ((leftmid1&0xFFFF) < (rightmid1&0xFFFF)) return -1;
    if ((leftmid1&0xFFFF) > (rightmid1&0xFFFF)) return 1;
    if ((leftlow&0xFFFF) < (rightlow&0xFFFF)) return -1;
    if ((leftlow&0xFFFF) > (rightlow&0xFFFF)) return 1;
    return 0;    
}






#include <iostream>
#include <random>
#include <climits>

template<int min, int max>
int randbetween() {
    const int range=max-min;
    const int extra = RAND_MAX % range;
    const int reroll = RAND_MAX-extra;
    int result;
    while((result=rand())>=reroll)
        ;
    return result;
}
void fail(int left1, int left2, int right1, int right2) {
    std::cout << "wrong result for "<<left1<<"*"<<left2<<">="<<right1<<"*"<<right2<<"\n";
}

int main() {
    srand(time(NULL));
    for(int i=0; i<100; ++i) {
        int left1 = randbetween<0x10000,INT_MAX>();
        int left2 = randbetween<0x10000,INT_MAX>();
        int right1 = randbetween<0x10000,INT_MAX>();
        int right2 = randbetween<0x10000,INT_MAX>();
        int compr = multiply_compare(left1, left2, right1, right2);
        long long realr = 1ll*left1*left2 - 1ll*right1*right2;
        switch(compr) {
        case -1: if (realr>=0) fail(left1, left2, right1, right2); break;
        case 0: if (realr!=0) fail(left1, left2, right1, right2); break;
        case 1: if (realr<=0) fail(left1, left2, right1, right2); break;
        }
    }
}