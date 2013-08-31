#include <stdint.h>
#include <stdio.h>


unsigned char buf[] = {
0x11, 0x22, 0x33, 0x44,
0x55, 0x66, 0x77, 0x88,
0x99, 0xaa, 0xbb, 0xcc
};


typedef struct mystruct {
 uint16_t var1;
 uint16_t var2;
 uint32_t var3;
 uint32_t var4;
} something;


int main(){

   printf("sizeof buf: %lu %d \n",sizeof(buf),sizeof(something));
   something *st = (something*)&(buf[0]);
   #define pr(a) printf(#a" %x\n",a)
   pr(st->var1);
   pr(st->var2);
   pr(st->var3);
   pr(st->var4);

   return(0);
}