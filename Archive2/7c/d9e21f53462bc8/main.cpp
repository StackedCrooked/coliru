#include <stdio.h>
#include <stdlib.h>
void play();
void quit();

int main()
{
    int x;
    printf("1) play\n2) quit\n");
    scanf("%d", x);
    switch(x) {
    case(1): {
        play();
        break;
    }
    case(2): {
        quit();
        break;
    }
    default:{
        printf("BAD INPUT");
        break;
    }

    /*if x is equal to 1, play
      if x is equal to 2, quit
      otherwise, tell the user, BAD INPUT*/
}

return 0;
}

void play(void){
    printf("play");
}