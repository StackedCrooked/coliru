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
    struct node* ptr1=head, *ptr2=head, *dup;
    while(ptr1 != NULL && ptr1->next != NULL)
    {
        ptr2=ptr1;
        while(ptr2->next!= NULL)
        {
            if(ptr1->data == ptr2->next->data)
            {
                dup = ptr2->next;
                ptr2->next = ptr2->next->next;
                free(dup);
            }
            else
                ptr2 = ptr2->next;        
        }
    ptr1 = ptr1->next;
    }
}
int main()
{
    struct node* head = NULL;
    push(&head,1);
    push(&head,2);
    push(&head,1);
    push(&head,3);
    push(&head,1);
    push(&head,2);
    print(head);
    printf("\nAfter removing duplicates:");
    duplicates(head);
    print(head);
}





















