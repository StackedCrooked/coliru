#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>


int main (int argc, char **argv)
{
   int c1 = 101010;
   int c2 = 110110;
   
   printf("c1: %d c2: %d", c1, c2);
   
   //cross over point
   int crossOverPoint = 3;
   int mask = 1;// 000001
   mask = mask << crossOverPoint; // 001000
   mask = 000111; // 000111
   
  // printf("\nmask: %d", mask);
   
   //tail end
   int c1_end = c1 & mask; //000010
   int c2_end = c2 & mask; //000110
   
   printf("\nIn swap:\nc1_end: %d c2_end: %d", c1_end, c2_end);
   
   //clear old tails
   int mask2 = 111000; //111000
   c1 = c1 & mask2; //101000
   c2 = c2 & mask2; //110000
   
  // printf("test mask: %d", mask2<<2);
   printf("\nIn swap:\nc1_head: %d c2_head: %d", c1, c2);
   
   printf("\nmask: %d mask2: %d", mask, mask2);
   //swap tails
   c1 = c1 | c2_end; //101110
   c2 = c2 | c1_end; //110010
   
   printf("\nAfter swap:\nc1: %d c2: %d", c1, c2);

   return 0;
}





