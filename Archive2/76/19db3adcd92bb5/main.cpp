#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

//convert decimal int to binary format int which is represented in a decimal format. 
//only for display, cannot be used for computing.
 unsigned int int_to_binary(unsigned int k) {
    return (k == 0 || k == 1 ? k : ((k % 2) + 10 * int_to_binary(k / 2)));
}

int main (int argc, char **argv)
{
   char chrom1[30] = "101010";
   char chrom2[30] = "110110";
   char mask1[30] = "000111";
   char mask2[30] = "111000";
   printf("Input c1: %s c2: %s\n", chrom1, chrom2);
   char *ptr1,*ptr2;

    //convert the above 4 string values to decimal int following binary rule.
   long ret1 = strtoul(chrom1, &ptr1, 2);
   long ret2 = strtoul(chrom2, &ptr2, 2);
   long m1 = strtoul(mask1, &ptr1, 2);
   long m2 = strtoul(mask2, &ptr2, 2);
   
   printf("The number(unsigned long integer) is %lu %lu\n", ret1,ret2);
    
   long child1 = (ret1 & m2) ^ (ret2 & m1);
   long child2 = (ret1 & m1) ^ (ret2 & m2);
   printf("Result of & is %d and %d\n", int_to_binary(child1),int_to_binary(child2));

   return 0;
}





