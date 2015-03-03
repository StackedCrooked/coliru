#include <stdio.h>
#include <string.h>
#define DENSITY 62.4
int main(){
    float w, v;
    int s, l;
    char name[40];
    printf("barev anund vonc e?\n");
    scanf("%s",name);
    printf("%s name\n", name);
    scanf("%f",&w);
    s = sizeof name;
    l = strlen(name);
    v = w / DENSITY;
    printf("%s ev %2.2f\n",name, v);
    printf("%d ",l);
    printf("%d",s);
    return 0;
    
    }