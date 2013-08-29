#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *scat(char *,char *);

void main()
{
    char *s="james";
    char *t="bond";

    char *w=scat(s,t);
    printf("the con: %s\n", w);
    free(w);
}

char *scat(char *s,char *t)
{ 
    char *p=malloc(strlen(s)+strlen(t)+1); 
    int temp=0 , ptr=0;

    while(s[temp]!='\0'){
        p[ptr++]=s[temp++];
    } 
    temp=0;
    while(t[temp]='\0'){
        p[ptr++]=t[temp++];
    }
    return p;
}