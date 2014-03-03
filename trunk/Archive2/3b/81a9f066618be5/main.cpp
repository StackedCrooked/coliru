#include <string.h>
#include <stdio.h>
 
int main() 
{
    char* string = "RIFF";
    char riff[4] = {'R','I','F','F'};
    if(strcmp(riff,string) != 0){
        printf("Takhle je videt proc to nematchuje?\n");
    }
    
 
   
}