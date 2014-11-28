#include<stdio.h>
#include<stdlib.h>
struct node
{
    int data;
    struct node* next;
};
void push(struct node** head, int data)
{
    struct node* temp = (struct node*) malloc(sizeof(struct node*));
    struct node* last = *head;
    temp->data = data;
    temp->next = NULL;
    if(*head == NULL)
    {
        *head = temp;
        return;
    }
    while(last->next != NULL)
    {
        last = last->next;
    }
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
// delete a single element
void deleteelement(struct node** head, int data)
{
    struct node* temp = *head;
    struct node* prev = *head;
    if(temp->data == data && temp->data == (*head)->data)
    {
        (*head) = (*head)->next;
        printf("deleted Node: %d",temp->data);
        free(temp);
        return;
    }
    while(temp->next != NULL)
    {
        if(temp->data ==data)
        {
            prev->next = temp->next;
        }
        prev = temp;
        temp = temp->next;
    }
}
//delete whole linked list
void deletelist(struct node* head)
{
    struct node* current=head;
    struct node* next;
    while(current !=NULL)
    {
        next = current->next;
        printf("\n Deleted element:%d  ",current->data);
        free(current);  
        current = next;
    }
    head = NULL;
}

int main()
{
    struct node* head=NULL;
    int i=1;
    for(;i<10;i++)
    {
        push(&head,i);
    }
    printf("\n Before deletion \n");
    print(head);
    deleteelement(&head,3);
    printf("\n After deletion \n");
    print(head);
    // deletelist(head);
}
