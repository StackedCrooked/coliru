#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main (int argc, char *argv[])
{
 if(argc != 3)/*argc should be 2 for correct execution*/
 {
  printf("usage: %s filename",argv[0]);
 }
 else
 {
  int file1 = open(argv[1], O_RDWR);
  if(file1 == -1){
    printf("\nfailed to open file.");
    return 1;
  }
  int reversefile = open(argv[2], O_WRONLY, O_CREAT);
  int size =(int)lseek(file1, 0, SEEK_END)+1;
  char file2[size];
  int count=size;
  int i = 0;
  char file[100];

  while(read(file1, &file2[count], 1) != 0)
  {
 
   count--;
   i++;
   }
 }
}