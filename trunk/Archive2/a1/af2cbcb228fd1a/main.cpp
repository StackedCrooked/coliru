#include <stdio.h>
#include <string.h>

int proba(char a[][3], int y1, int x1){
    char s[1000];
    int br,broj;
    br=0;
    s[0]='\0';
    printf("%d\n", x1);
    while((y1!=3) && (x1!=3)){
      s[br]=a[y1][x1];
      printf("s= %s\n", s);
      y1=y1+1;
      x1=x1+1;
      br++;
    }
    printf("%s\n", s);
    broj= count("a",s);
    s[0]='\0';
    return broj;
}


int main(void) {
const char *needle;
int konacno,n,i;
konacno=0;
n=3;
char stack[3][3]={{'a','a','a'},{'b','b','b'},{'c','c','c'}};
konacno=konacno+proba(stack, 0,0);
konacno=konacno+proba(stack, 0,1);
printf("%d", konacno);
return 0;
}