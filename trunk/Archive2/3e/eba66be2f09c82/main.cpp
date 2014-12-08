#include<stdio.h>
#include<stdlib.h>
struct node
{
    int data;
    struct node* next;
};
void Push(struct node** head, int data)
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
        last=last->next;
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
int comparelist(struct node* head1 , struct node* head2)
{
    struct node* temp1 = head1;
    struct node* temp2 = head2;
    while(temp1 && temp2)
    {
        if( temp1->data == temp2->data)
        {
        temp1 = temp1->next;
        temp2 = temp2->next;
        }
        else
            return 0;
    }
        if( temp1 == NULL && temp2 == NULL)
            return 1;
        return 0;
}
void palindrom(struct node* head)
{
    struct node* slow_ptr=head,*fast_ptr=head;
    struct node* second_half, *prev_of_slow_ptr = head;
    struct node* midnode = NULL;
    int result = 1;
    if(head !=NULL && head->next!=NULL)
    {
        while(fast_ptr != NULL && fast_ptr->next != NULL)
        {
            fast_ptr = fast_ptr->next->next;
            prev_of_slow_ptr = slow_ptr;
            slow_ptr = slow_ptr->next;
        }
        if(fast_ptr != NULL)
        {
            midnode = slow_ptr;
            slow_ptr = slow_ptr->next;
        }
        second_half = slow_ptr ;
        prev_of_slow_ptr->next = NULL;
        reverse(&second_half);
        result = comparelist(head , second_half);
        reverse(&second_half);
        if(midnode!=NULL)
        {
            prev_of_slow_ptr->next = midnode;
            midnode->next = second_half;
        }
        else
        prev_of_slow_ptr->next = second_half;
    }
    if(result)
        printf("Palindrom \n");
    else 
        printf("Not Palindrom \n");
}
int main()
{
    struct node* head = NULL;
    Push(&head,1);
    Push(&head,2);
    Push(&head,3);
    Push(&head,2);
    Push(&head,1);
    print(head);
    palindrom(head);
}
