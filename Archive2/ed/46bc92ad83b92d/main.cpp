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

void add(Node *& head, int data)
{
    if (head)
    {
        Node *temp = head;
        Node *last;
        while (temp)
        {
           last = temp;     
           temp = temp->link;
        }
        last->link = new Node{data, NULL};
    }    
    else
       prepend(data, head);
}
        

int main()
{
  Node *head = new Node{0, NULL};
  add(head, 1);
  add(head, 2);
  add(head, 3);
  add(head, 4);
  add(head, 5);
  add(head, 6);
  print(head);
  works(head);
  print(head);
}