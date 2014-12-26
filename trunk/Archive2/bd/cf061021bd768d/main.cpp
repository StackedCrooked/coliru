#include <stdio.h>
#include <stdlib.h>

typedef char ElemType;
typedef struct Queue{
ElemType data;
struct Queue *next;
}Queue,*pQueue;

pQueue CreateQueue()
{
pQueue p=(pQueue)malloc(sizeof(Queue));
p->next=NULL;
return p;
}
int isEmpty(pQueue Q)
{
if(Q->next==NULL)
   return 1;
else
return 0;
}
void Push(pQueue *Q,ElemType a)
{
pQueue p=(pQueue)malloc(sizeof(Queue));
if(!p)
{
   printf("内存分配失败！\n");
return;
} 
p->data=a;
p->next=NULL;
(*Q)->next=p;
(*Q)=p;
}
void Pop(pQueue Q)
{
pQueue p ; 
if(isEmpty(Q))
{
printf("空队列!\n");
return; 
}
else
{
   p=Q->next;
   Q->next=Q->next->next;
   free(p);
    } 
}
ElemType Top(pQueue Q)
{
return Q->next->data;
}


int main(int argc, char *argv[]) {
pQueue begin;
char c;
pQueue Q=CreateQueue();
begin=Q;
while((c=getc(stdin))!='\n')
   Push(&Q,c);
while(!isEmpty(begin))
{
printf("%c\n",Top(begin));
Pop(begin);
}
system("pause");
return 0;
}