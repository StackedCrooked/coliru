#include<stdio.h>
#include<stdlib.h>
struct node
{
    int data;
    struct node* next;
};
struct node* push( struct node** head, int data)
{
    struct node* temp = *head;
    struct node* temp1 = (struct node*)malloc(sizeof(struct node*));
    temp1->data = data;
    temp1->next = NULL;
    if(*head == NULL)
    {
        *head = temp1;
        return 0;
    }
    while(temp->next != NULL)
        temp = temp->next;
    temp->next = temp1;
    return 0;
}
void print(struct node* head)
{
    while(head!= NULL)
    {
        printf("%d  ",head->data);
        head = head->next;
    }
}
void duplicates(struct node* head)
{
    struct node* temp = head;
    struct node* dummy=NULL;
    while( temp->next != NULL)
    {
        if( temp->data == temp->next->data)
        {
            dummy = temp->next;
            temp->next = temp->next->next;
            free(dummy);
        }
        else
            temp = temp->next;
    }     
}
int main()
{
    struct node* head = NULL;
    push(&head,10);
    push(&head,20);
    push(&head,20);
    push(&head,30);
    push(&head,30);
    push(&head,30);
    print(head);
    printf("\nAfter removing duplicates:");
    duplicates(head);
    print(head);
}





















