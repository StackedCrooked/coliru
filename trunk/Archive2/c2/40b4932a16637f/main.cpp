#include <iostream>

struct Node
{
    int data;
    Node *link;
};


void works(Node* &head)
{
    Node *temp;
    Node *tail;
    
    temp = head; //head is initialized to point at the first node in the list.     
    
    for(tail = head; tail -> link != NULL; tail = tail -> link)
    {
      ;
    } 
    //Sets tail pointer to the last node in the list
    
    head = head -> link; //sets head to the second node/new first node
    tail -> link = temp; //sets the link field of what tail points at to what temp points at
    temp -> link = NULL; //sets the last node to point at NULL
}


void prepend(int i, Node* &head)
{
    Node *n = new Node{i, head};
    head = n;
}

void print(Node *n)
{
    while (n)
    {
        std::cout << n->data;
        n = n->link;
    }
    std::cout << '\n';
}


int main()
{
    Node *head = new Node{5, NULL};
    prepend(4, head);
    prepend(3, head);
    prepend(2, head);
    prepend(1, head);
    prepend(0, head);
    print(head);
    works(head);
    print(head);
}