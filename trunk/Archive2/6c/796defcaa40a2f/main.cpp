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
    struct node* last = *head;
    temp->data = data;
    temp->next = NULL;
    if(*head == NULL)
    {
        *head = temp;
        return;
    }
    while(last->next != NULL)
        last = last->next;
    last->next = temp;
}
void print(struct node* head)
{
    while(head != NULL)
    {
        printf("%d  ",head->data);
        head = head->next;
    }
}
void nthfromlast(struct node** head, int loc)
{
    struct node* temp1 = *head;
    struct node* temp2 = *head;
    int count=1;
    while(count<loc)
    {
        temp1 = temp1->next;
        count++;
    }
    while(temp1->next != NULL)
    {
        temp1 = temp1->next;
        temp2 = temp2->next;
    }
    printf("\nNth node from last :%d\n",temp2->data);
}
int main()
{
    struct node* head = NULL;
    int i=1;
    for (;i<10;i++)
        push(&head,i);
    print(head);
    nthfromlast(&head,5);
}
