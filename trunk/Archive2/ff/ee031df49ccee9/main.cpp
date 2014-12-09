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
    printf("\n");
}
int count(struct node* head)
{
    int c=0;
    while(head!=NULL)
    {
        c++;
        head = head->next;
    }
    return c;
}
int __getIntesectionNode(int d,struct node* head, struct node* head1)
{
    int i;
    for(i=0;i<d;i++)
    {
        if(head == NULL)
        {
            return -1;
        }
        head = head->next;
    }
    while(head != NULL && head1 != NULL)
    {
        if(head == head1)
        {
            return head->data;
        }
        head = head->next;
        head1 = head1->next;
    } 
    return 0;
}
int getIntesectionNode(struct node* head1, struct node* head2)
{
    int c1,c2,d;
    c1 = count(head1);
    c2 = count(head2);
    if(c1>c2)
    {
        d = c1-c2;
        return __getIntesectionNode(d,head1,head2);
    }
    else 
    {
        d = c2-c1;
        return __getIntesectionNode(d,head2,head1);
    }
}
int main()
{
  /*
    Create two linked lists
 
    1st 3->6->9->15->30
    2nd 10->15->30
 
    15 is the intersection point
  */
 
  struct node* newNode;
  struct node* head1 =(struct node*) malloc(sizeof(struct node));
  head1->data  = 10;
  struct node* head2 =(struct node*) malloc(sizeof(struct node));
  head2->data  = 3;
 
  newNode = (struct node*) malloc (sizeof(struct node));
  newNode->data = 6;
  head2->next = newNode;
 
  newNode = (struct node*) malloc (sizeof(struct node));
  newNode->data = 9;
  head2->next->next = newNode;
 
  newNode = (struct node*) malloc (sizeof(struct node));
  newNode->data = 15;
  head1->next = newNode;
  head2->next->next->next  = newNode;
 
  newNode = (struct node*) malloc (sizeof(struct node));
  newNode->data = 30;
  head1->next->next= newNode;
 
  head1->next->next->next = NULL;
  
  print(head1);
  print(head2);
 
  printf("The node of intersection is %d \n",
          getIntesectionNode(head1, head2));
 
  getchar();
}
