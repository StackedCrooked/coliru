#include<stdio.h>
#include<stdlib.h>
struct node{
    int key,info;
    struct node *next;
};
struct node *head,*z;
void initialize()
{
    head=(struct node*)malloc(sizeof *head);
    z=(struct node*)malloc(sizeof *z);
    head->next=z;z->next=z;
    z->key=-1;
}
void insert(int n,int info)
{
    struct node* t,*x;
    t=head;
    while(t->next!=z)
    {
        t=t->next;
    }
    x=(struct node *)malloc (sizeof *x);
    x->key=n;
    x->next=t->next;
    t->next=x;
    x->info=info;

}
void show()
{
    struct node *t=head;
    while(t->next!=z)
    {
        t=t->next;
        printf("%d\t%d\n",t->key,t->info);
    }

}
int main()
{
    initialize();
    int i=4,j=5;

    printf("enter the number and info\n");
    scanf("%d%d",&i,&j);//i is key and j is info 
    insert(i,j);//passing arguments to insert function
    show();
    return 0;
}