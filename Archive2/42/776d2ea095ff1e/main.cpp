#include<stdio.h>
#include<stdlib.h>
struct node
{
    int data;
	struct node* next;
};
void push(struct node** head, int data)
{
	struct node* temp = (struct node*)malloc(sizeof(struct node*));
	struct node* dummy = *head;
	temp->data = data;
	temp->next = NULL;
	if(*head == NULL)
	{
		*head = temp;
		return;
	}
	while(dummy->next != NULL)
		dummy = dummy->next;
	dummy->next = temp;
}
void print (struct node* head)
{
    while(head != NULL)
    {
        printf("%d  ",head->data);
        head = head->next;
    }
}
void count(struct node* head,int data)
{
    int count=0;
    while(head != NULL)
    {
        if(head->data == data)
            count++;
        head = head->next;
    }
    printf("\nNumber %d occurs in list is:%d\n",data,count);
}
int main()
{	
	struct node* head=NULL;
	int i=1;
	for(;i<10;i++)
	{
		push(&head,i);
	}
    push(&head,3);
    push(&head,3);
    print(head);
    count(head,3);
}
