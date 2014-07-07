#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
using namespace std;

#define USETW(w,v) ((w)[0] = (u_int8_t)(v), (w)[1] = (u_int8_t)((v) >> 8))

int main ()
{
    
    unsigned short b=0x00;
    uint8_t a[2];
    a[0]=0;
    a[1]=1;
    printf("a=[%x][%x]\n", a[0], a[1]);
    printf("b=[%x]\n", b);
    b=0x0f;
    USETW(a, b);
    printf("a=[%x][%x]\n", a[0], a[1]);
    printf("b=[%x]\n", b);
    
    printf("[%d]", 2);
    /*
  FILE * pFile;
  pFile = fopen ("myfile.txt","wt");
  fprintf (pFile, "fclose example");
  fclose (pFile);
  pFile = NULL;
  if(pFile == NULL){
      printf("NUKK");
  }else{
      printf("NOT NULL");
  }
  //*/
  /*
  uint16_t sum1=0xff;
  uint16_t sum2=0xff;
  uint16_t nextsum1=0xff;
  uint16_t nextsum2=0xff;
  unsigned short magic =0;
  while((sum2<0xffff)){
      sum2 += (sum1 += 0xff);
      
      nextsum2 += (nextsum1 += 0xff);
      nextsum2 += (nextsum1 += 0xff);
      
      if(nextsum2 < sum2){
          printf("This number = [%lx]\n", sum2);
          printf("is bigger than the next number = [%lx]\n", nextsum2);
          printf("That means there is overflow...\n");
          break;
      }
      nextsum1 = sum1;
      nextsum2 = sum2;
      magic++;
  }
  printf("magic number = [%u]\n", magic);
  //*/
  return 0;
}
