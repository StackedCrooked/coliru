int logicalByteAdd(int x, int y) {
    int z=0,c=0;
    for(int i=0;i<32;++i) {
        switch((x>>i&1)<<2|(y>>i&1)<<1|c) {
        case 0: break;
        case 1: z|=(1<<i); c=0; break;
        case 2: z|=(1<<i); break;
        case 3: break;
        case 4: z|=(1<<i); break;
        case 5: break;
        case 6: c=1; break;
        case 7: z|=(1<<i); break;
        }
    }
    return z;
}

#include <iostream>
int main() {
    for(int x=0; x<11; ++x) {
        for(int y=0; y<11; ++y) {
            int z = logicalByteAdd(x,y);
            std::cout<<x<<'+'<<y<<'='<<z<<(z==x+y?"\n":" fail\n");
        }
    }
}