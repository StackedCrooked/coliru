#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
char buffer[1024];

int main(int argc,char** argv)
{

  strcpy(buffer,"");
  strcat(buffer,"%");
  strcat(buffer,"");
  strcat(buffer,"%");
  printf(buffer);
  printf("\n");

}



