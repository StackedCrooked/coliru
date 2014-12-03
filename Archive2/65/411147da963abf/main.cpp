#include <stdio.h>

using namespace std;

int main()
{
int x=3;
int i;
char c='$';
printf("please enter diagonak length\n");
scanf("%d",&x);
printf("please choose a symbol\n");
scanf("%c",&c);


for(i=1;i<x;i++){
    printf(" ");
}
printf("%c_Odelya Azrad_%c\n",c,c);

}