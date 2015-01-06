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

int fitness(char *chrom, int length){
    int fitness=0;
    for(int i=0;i<length;i++){
     if(chrom[i]=='1')   fitness++;
    }
    return fitness;
}

  void mutate(char *chrom, int length, float mutationRate) {
    for (int i = 0; i < length; i++) {
      if (random(1) < mutationRate) {
        chrom[i] = ~chrom[i];
      }
    }
  }

int main (int argc, char **argv)
{
    char **population; //include every parent that is about to have childen
    //long long type can represent upto 20 bits of 1 and 0, 
    //chroms longer than 20bits will be splited to array of long long numbers
   char chrom1[] = "10101010001101011";
   char chrom2[] = "11010000110010010";
   int length = sizeof(chrom1)-1;
   double crossover = (double)0.5; //this determines the crossover point in chrom
   
   //generate mask for crossover
   char *mask1 = (char *) malloc(length*sizeof(char));
   char *mask2 = (char *) malloc(length*sizeof(char));
   generate_mask(mask1, mask2, length, crossover);
   printf("input  1: %15s (%d) 2: %15s (%d) Length: %d\n", chrom1, fitness(chrom1,length), chrom2, fitness(chrom2, length), length);
   printf("masks  1: %15s 2: %15s\n", mask1, mask2);
   char *ptr1,*ptr2;

    //convert the above 4 string values to decimal int following binary rule.
   long long ret1 = strtoul(chrom1, &ptr1, 2);
   long long ret2 = strtoul(chrom2, &ptr2, 2);
   long long m1 = strtoul(mask1, &ptr1, 2);
   long long m2 = strtoul(mask2, &ptr2, 2);
   
   //crossover operation 
   long long ichild1 = (ret1 & m2) ^ (ret2 & m1);
   long long ichild2 = (ret1 & m1) ^ (ret2 & m2);
   //convert binary format childern to string, in order to add them to parent pool.
   char *child1 = (char *)malloc(length * sizeof(char));
   char *child2 = (char *)malloc(length * sizeof(char));
   sprintf(child1,"%lld",int_to_binary(ichild1));
   sprintf(child2,"%lld",int_to_binary(ichild2));
   
   printf("child 1: %18s 2: %s",child1,child2);

   return 0;
}





