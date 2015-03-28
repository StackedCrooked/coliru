#include<stdio.h>
#define S_TO_M 60
int main(void)
{
    int sec,min,left;

    printf("This program converts seconds to minutes and ");
    printf("seconds. \n");
    printf("Just enter the number of seconds. \n");
    printf("Enter 0 to end the program. \n");
    printf("sec = %d\n",sec);
    while(sec > 0)
    {
        scanf("%d",&sec);
        min = sec/S_TO_M;
        left = sec % S_TO_M;
        printf("%d sec is %d min, %d sec. \n",sec,min,left);
        printf("Next input?\n");
    }
printf("Bye!\n");

return 0;
} 