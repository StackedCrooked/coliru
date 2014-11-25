#include<stdio.h>
#include<stdlib.h>
struct Node{
int data;
struct Node *next;
};
void printlist(struct Node* n)
{
    while(n != NULL)
    {
        printf("%d ",n->data);
        n = n->next;
    }
}
void addatbeg(struct Node** head, int data)
{
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node*));
    new_node->data = data;
    new_node->next = *head;
    *head = new_node;
}
void append(struct Node** head, int data)
{
    struct Node* new_node= (struct Node*) malloc(sizeof(struct Node*));
    struct Node* last = *head;
    new_node->data = data;
    new_node->next = NULL;
    
    if( *head == NULL)
    {
        printf("List is Empty");
        *head = new_node;
        return;
    }
    while(last->next != NULL)
        last = last->next;
    last->next = new_node;    
}
//Insert an element after specified location
void insertafter(struct Node** head, int loc,int data)
{
    int i=0;
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node*));
    struct Node* dummy = *head;
    new_node->data = data;
    if((*head) == NULL)
    {   
        printf("No elements");
        return;
    }
    while(i<loc-1)
    {
        i++;
        dummy = dummy->next;
    }
    new_node->next = dummy->next;
    dummy->next = new_node;        
}
void del(struct Node** head, int data)
{
    struct Node* temp = *head, *prev;
    prev = NULL;
    if(temp!= NULL && temp->data == data)
    {
        *head = temp->next;
        free(temp);
    }
    while(temp != NULL && temp->data != data)
    {
        prev = temp;
        temp=temp->next;
    }
    if(temp == NULL)
        printf("Element not Found");
        
    prev->next = temp->next;
    free(temp);
}

/* delete the specific node by passing that address
{
    struct Node* temp = node_ptr->next;
    node_ptr->data = temp->data;
    node_ptr->next = temp->next;
    free(temp);
}*/
int main()
{
    struct Node* first;
    struct Node* second;
    struct Node* third;
    first  = (struct Node*)malloc(sizeof(struct Node*));
    second  = (struct Node*)malloc(sizeof(struct Node*));
    third  = (struct Node*)malloc(sizeof(struct Node*));
    
    first -> data = 1;
    first -> next = second;
    
    second -> data = 2;
    second -> next = third;
    
    third -> data = 3;
    third -> next = NULL;
    
    addatbeg(&first,10);
    
    append(&first,100);
    
    insertafter(&first,2,80);
    
    del(&first,3);
    
    printlist(first);
    
    return 0;
}
