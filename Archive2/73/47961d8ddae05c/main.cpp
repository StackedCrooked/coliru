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

void reverse(struct node** head)
{
        struct node* prev = NULL;
        struct node* current = *head;
        struct node* next;
        while(current != NULL)
        {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        *head = prev;
}
struct node* recursiveprint(struct node* head)
{
    if(head != NULL)
    {
        recursiveprint(head->next);
        printf("%d  ",head->data);
    }
    
}
int main()
{	
	struct node* head=NULL;
	int i=1;
	for(;i<10;i++)
	{
		push(&head,i);
	}
    print(head);
    reverse(&head);
    printf("\nReverse of a linked list:");
    print(head);
    printf("\nRecursive method of a linked list:");
    recursiveprint(head);
}
