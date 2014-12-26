#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;
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

void Push(pQueue *Q,ElemType a)
{
	pQueue p=(pQueue)malloc(sizeof(Queue));
	p->data=a;
	p->next=NULL;
	(*Q)->next=p;
	(*Q)=p;
}
void Pop(pQueue q)
{
	pQueue p=q->next;
	q->next=q->next->next;
	free(p);
}
ElemType Top(pQueue Q)
{
	return Q->next->data;
}
int isEmpty(pQueue Q)
{
	if(Q->next==NULL)
	    return 1;
	return 0;
}
int main(int argc, char *argv[]) {
	int i;
	pQueue p;
	pQueue Q=CreateQueue();
	p=Q;
	for(i=0;i<10;++i)
	    Push(&Q,i);
	while(isEmpty(Q))
	{
		printf("%d\n",Top(p));
		Pop(p);
	}
	system("pause");
	return 0;
}