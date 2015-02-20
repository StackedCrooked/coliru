#include <stdio.h>
#include <string.h>
void fill(char a[],char Y,char N){
    for(int i=0;i<1000&&a[i];++i)a[i]=(i%2?N:Y);
}
int main(int argc,char*argv[]){
    char arr_odd[]="abcdefghi";
    fill(arr_odd,'Y','N');
    
    char arr_even[]="abcdefghij";
    fill(arr_even,'Y','N');
    printf("%s\n%s\n",arr_odd,arr_even);
    
    char arr_max[1000];
    memset(arr_max,1,1000-1);
    arr_max[999]=0;
    fill(arr_max,'Y','N');
    
    printf("%s\n%s\n%s\n",arr_odd,arr_even,arr_max);
    return 0;
}