#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

//convert decimal int to binary format int which is represented in a decimal format. 
//only for display, cannot be used for computing.
 unsigned long long int_to_binary(unsigned long long k) {
    return (k == 0 || k == 1 ? k : ((k % 2) + 10 * int_to_binary(k / 2)));
}

 void generate_mask(char *mask1,char *mask2, int length, double crossover){
    int i;
    for(i=0;i<length; i++){
        if(i<length*crossover){
           mask1[i]='0';
           mask2[i]='1';
        }else{
           mask1[i]='1';
           mask2[i]='0';
        }
    }
}

int main (int argc, char **argv)
{
    //long long type can represent upto 20 bits of 1 and 0, 
    //chroms longer than 20bits will be splited to array of long long numbers
   char chrom1[30] = "101010100011010111";
   char chrom2[30] = "110100001100100101";
   int length = 18;
   double crossover = (double)0.1; //this determines the crossover point in chrom
   char *mask1 = (char *) malloc(length*sizeof(char));
   char *mask2 = (char *) malloc(length*sizeof(char));
   generate_mask(mask1, mask2, length, crossover);
   printf("input  1: %15s 2: %15s\n", chrom1, chrom2);
   printf("masks  1: %15s 2: %15s\n", mask1, mask2);
   char *ptr1,*ptr2;

    //convert the above 4 string values to decimal int following binary rule.
   long long ret1 = strtoul(chrom1, &ptr1, 2);
   long long ret2 = strtoul(chrom2, &ptr2, 2);
   long long m1 = strtoul(mask1, &ptr1, 2);
   long long m2 = strtoul(mask2, &ptr2, 2);
    
   long long child1 = (ret1 & m2) ^ (ret2 & m1);
   long long child2 = (ret1 & m1) ^ (ret2 & m2);
   printf("Result 1: %14lld 2: %14lld\n", int_to_binary(child1),int_to_binary(child2));

   return 0;
}





