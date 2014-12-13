#include<stdio.h>
#include<stdlib.h>
struct node{
    int data;
	struct node* next;
};
void push(struct node** head, int data)
{
	struct node* temp=*head;
	struct node* dummy = (struct node*) malloc(sizeof(struct node*));
	dummy->data = data;
	dummy->next = NULL;
	if(*head == NULL)
	{
		*head = dummy;
		return;
	}
	while(temp->next!= NULL)
		temp = temp->next;
	temp->next = dummy;
}
void print(struct node* head)
{
	while(head!=NULL)
	{
		printf("%d  ",head->data);
		head = head->next;
	}
}
void swap(int *a, int *b)
{
    int temp;
    temp=*a;
    *a=*b;
    *b=temp;
}
void lastnodeswap(struct node* head)
{
    struct node* temp = head;
    while(temp->next!= NULL)
        temp= temp->next;
    swap(&head->data,&temp->data);
}
int main()
{
	struct node* head = NULL;
	push(&head,1);
	push(&head,2);
	push(&head,3);
	push(&head,4);
	push(&head,5);
	printf("Linked list before swapping:\n");
	print(head);
	lastnodeswap(head);
	printf("\nLinked list after swapping:\n");
	print(head);
}