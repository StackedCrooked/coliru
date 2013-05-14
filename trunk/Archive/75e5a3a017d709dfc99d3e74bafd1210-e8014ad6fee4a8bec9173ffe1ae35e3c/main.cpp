#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv) {
  int posX = 1;
  int posY = 1;
  const char* worm = argv[1]; 
  
  for (int i = 0; i < 100; i++) {
    printf("\x1b[%d;%dH", posX, posY); // Put cursor in position posX, posY
    printf("%c", worm[0]);  // Print first character of worm 
  }
}