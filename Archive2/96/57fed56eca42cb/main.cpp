#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main() 
{
    int varb;
    
    char *string = "varb=2345";
    char *findequal = strrchr(string, '=');
    char *var_b_value = findequal ? findequal + 1 : string;
    int var_name_size = findequal - string;
    int xunga = atoi( var_b_value);
    
    printf("%d\n", var_name_size);
    
    
    char var[var_name_size + 1];
    
    strncpy(var, string, var_name_size);
    var[var_name_size] = '\0';
    
    printf("%s\n", var_b_value);
    printf("%s\n", var);
    
    //Matches
    int a = strcmp(var, "varb");
    if (a == 0) {
        printf("Strings are matching.\n");
        varb = xunga;
        printf("varb = %d\n", varb);
    }
     
    if(a!=0)
        printf("not");
       
}