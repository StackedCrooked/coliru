#include<stdio.h>
#include<stdlib.h>
struct node{
    int data;
    struct node* next;
};
void push(struct node** head,int data)
{
    struct node* temp= (struct node*) malloc(sizeof(struct node*));
    struct node* dummy = *head;
    temp->data = data;
    temp->next = NULL;
    
    if(*head == NULL)
    {
        *head = temp;
        return;
    }   
    while(dummy->next != NULL)
        (dummy)=(dummy)->next;
    (dummy)->next = temp;
}
void print(struct node* head)
{
    while(head!=NULL)
    {
        printf("%d->",head->data);
        head=head->next;
    }
}
void middle(struct node* head)
{
    struct node* slow_ptr,*fast_ptr;
    slow_ptr = head;
    fast_ptr = head;
    while(fast_ptr != NULL && fast_ptr->next != NULL)
    {
        slow_ptr= slow_ptr->next;
        fast_ptr= fast_ptr->next->next;
    }
    printf("\nMiddle Element:%d\n",slow_ptr->data);
}
int main()
{
    struct node* head= NULL;
    int i=1;
    for(;i<=5;i++)
    {
        push(&head,i);
    }
    print(head);
    middle(head);
}
