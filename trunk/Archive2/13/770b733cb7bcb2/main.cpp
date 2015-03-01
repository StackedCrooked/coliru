#include <stdio.h>
#define MAX_STACK 1024
const char src[]="1 2 + 3 *";
struct Operators{
    int(*func)(int,int);
    char symbol;
};
int add(int a,int b){return a+b;}
int sub(int a,int b){return a-b;}
int mul(int a,int b){return a*b;}
int div(int a,int b){return a/b;}
const struct Operators ops[]={
    {add,'+'},
    {sub,'-'},
    {mul,'*'},
    {div,'/'}
};
int eval(const char *src){
    int stack[MAX_STACK],cur_stack=0;
    while(*src){
        if(*src==' '){
            src++;
            continue;
        }
        int i;
        for(i=0;i<sizeof(ops)/sizeof(*ops);++i)if(*src==ops[i].symbol)break;
        if(i<sizeof(ops)/sizeof(*ops)){
            int a=stack[cur_stack-2],b=stack[cur_stack-1];
            cur_stack-=2;
            stack[cur_stack++]=ops[i].func(a,b);
            ++src;
            continue;
        }
        int c;
        sscanf(src,"%d%n",&stack[cur_stack++],&c);
        src+=c;
    }
    return stack[0];
}
int main(int argc,char*argv[]){
    printf("%s -> %d\n",src,eval(src));
    return 0;
}