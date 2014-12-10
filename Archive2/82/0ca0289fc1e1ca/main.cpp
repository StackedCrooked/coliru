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
void reverse(struct node* head)
{
    if(head!= NULL)
    {
        reverse(head->next);
        printf("%d  ",head->data);
    }
}
int main()
{
    struct node* head = NULL;
    int i=1;
    for(;i<10;i++)
        push(&head,i);
    print(head);
    printf("\nReverse Order:");
    reverse(head);
}
