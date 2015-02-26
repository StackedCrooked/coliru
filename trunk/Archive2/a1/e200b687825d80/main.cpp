#include <iostream>

struct node
{
    int value;
    node *next;
};

node * AddNode( node *head, int value )
{
    return head = new node { value, head };
}

void PrintList( node *head )
{
    for ( ; head != nullptr; head = head->next )
        std::cout << head->value << ' ';
    std::cout << std::endl;
}


void SwapList(node* head){
    node* temp = head->next; //head->next is second-node which needs to first one
    if (temp!= nullptr && temp->next!=nullptr){
        head->next=temp->next;  //move second node to first
        temp->next = head->next->next; //put second's next in first's
        head->next->next= temp; //and first will be second's next
        temp = nullptr; // swaping done
        SwapList(head->next->next); //do it for next couple
    }
}


int main() 
{
    node *head = nullptr;

    for ( int i = 10; i != 0; )
        head = AddNode( head, --i );

    PrintList( head );
   node * ptr2head=new node{-1,head};
    SwapList( ptr2head );
    head=ptr2head->next;

    PrintList( head );

}