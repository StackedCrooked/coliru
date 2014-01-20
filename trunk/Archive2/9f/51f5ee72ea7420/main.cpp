    #include <stdio.h>
    #include <time.h>
    #include <stdlib.h>
     
    int main (void)
    {
    srand(time(0));
     
    int a = 1 + rand() % 5;
     
    printf ("%d\n", a);
     
    return 0;
    }