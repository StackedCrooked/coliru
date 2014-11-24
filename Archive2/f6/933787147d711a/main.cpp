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
    
    printlist(first);
    
    return 0;
}
