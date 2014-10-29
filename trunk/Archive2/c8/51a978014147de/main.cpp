#include <cstdlib>
#include <iostream>

using namespace std;

struct Node {
    int data;
    Node *next;
};

struct UBList {
    void sort();
    Node *head;
};

void UBList::sort()
{
Node *a,*b;
int temp;
cout<<"\n\t\t*****Sort*****\n";

for(a = head; a != NULL; a = a -> next)
{
    for(b = a; b != NULL; b = b -> next)
    {
        if(a -> data > b -> data)
        {
            temp = a -> data;
            a -> data = b -> data;
            b -> data = temp;
        }
    }
  }
}