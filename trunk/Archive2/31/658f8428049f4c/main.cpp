#include <iostream>
#include <stdio.h>

using namespace std;

struct node
{
       int data;
       node *link;
};

int main()
{   
    node *h;
    node *i;
    node *j;
    
    h = new node;
    h->data = 2;
    
    i = new node;
    i->data = 15;
    h->link = i; 
    
    j = new node;
    j->data = 8;
    i->link = j;
    
    i = new node;
    i-> data = 24;
    j->link = i;
    
    j = new node;
    j->data = 63;
    i->link = j;
    
    i = new node;
    i->data = 77;
    j->link = i;
    i->link = NULL;
    i = h;
    j = h;

    cout << "From head to tail:" << endl;

    while( h != NULL)
    { cout << h->data << endl;
      h = h->link;
    }
    
    system("Pause");
    return 0;
}
    
