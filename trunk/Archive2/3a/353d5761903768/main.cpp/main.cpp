#include<iostream>

struct node
{
    int data;
    node* next;
};

void push(node* &head,int key)// Inserts items at front of link list
{
    node* linkNode=new node(); //declares new node
    linkNode->data=key;
    if(head==NULL)             //if the link list is empty then create a new one.
    {
        linkNode->next=NULL;
        head=linkNode;   //1
    }
    else
    {
        linkNode->next=head;
        head=linkNode;
    }    
}

void push2(node** head, int key)// Inserts items at front of link list
{
    node* linkNode=new node(); //declares new node
    linkNode->data=key;
    if(head==NULL)             //if the link list is empty then create a new one.
    {
        linkNode->next=NULL;
        *head=linkNode;
    }
    else
    {
        linkNode->next=*head;
        *head=linkNode;
    }    
}


void print(node* ptr)
{
    while(ptr)
    {
        std::cout << ptr->data << "->";
        ptr = ptr->next;
    }
    std::cout << "END\n";
}

int main(int argc, char** argv) 
{
    node* head=NULL;         //initializing head to NULL
    push(head,2);           //creating link list
    push(head,4);           //this requires &head
    push(head,8);           //link list is 8,4,2
    //selectSort(head);        //this does not require &head
    //reverse(head);          //this requires &head
    print(head);
    std::cout << "============" << std::endl;
    push2(&head, 10);
    push2(&head, 42);
    print(head);
    return 0;
}