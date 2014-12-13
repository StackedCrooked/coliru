#include<stdio.h>
#include<stdlib.h>
struct node{
    int data;
	struct node* next;
};
void push(struct node** head, int data)
{
	struct node* temp=*head;
	struct node* r = (struct node*)malloc(sizeof(struct ndoe*));
	r->data = data;
	r->next = NULL;
	if(*head == NULL || (*head)->data > data)
    {
        *head = r;
        (*head)->next = temp;
    }
    else
    {
        while(temp->next!=NULL)
        {
            if(temp->data<data &&((temp->next->data > data )||temp->next == NULL))
            {
                    r->next = temp->next;
                    temp->next = r;
                    return;
            }
            temp = temp->next;
        }
        temp->next = r;
    }
}
void deletion(struct node* head)
{
    struct node* temp=NULL;
    while(head != NULL)
    {
        temp = head->next;
        head->next = temp->next;
        free(temp);
        head = head->next;
    }
}
void print(struct node* head)
{
	while(head!=NULL)
	{
		printf("%d  ",head->data);
		head = head->next;
	}
}
int main()
{
	struct node* head = NULL;
	push(&head,1);
	push(&head,7);
	push(&head,5);
	push(&head,15);
	push(&head,10);
    push(&head,50);
	printf("Linked list before deletion:\n");
	print(head);
    deletion(head);
    printf("Linked list after deletion:\n");
    print(head);
}








