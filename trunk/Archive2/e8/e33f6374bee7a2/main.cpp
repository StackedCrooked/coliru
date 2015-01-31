#include <iostream>
#include <iterator>
using namespace std;

struct node
{
    node(int d, node* n = 0)
        : data(d)
        , next(n)
    {}
    int data;
    node* next;
};

void push(node*& n, int value)
{
    node** cur = &n;
    while (*cur)
        cur = &cur[0]->next;
    *cur = new node(value);
}

void display(node* n)
{
    if (n)
    {
        std::cout << n->data << " ";
        if (!n->next) std::cout << '\n';
        display(n->next);
    }
}

void delete_last_element(node*& head)
{
    if (head == nullptr) // list is empty, nothing to do
        return;

     if (head->next == nullptr) // only one element in list
     {
         delete head;
         head = nullptr; // set back to nullptr
         return; // get outta here
     }

     node *prev = nullptr,
          *curr = head;

     while (curr->next)
     {
         prev = curr;
         curr = curr->next;
     }

     delete curr;
     prev->next = nullptr;
}

int main()
{
    node* head;
    for (int i =0; i < 5;++i)push(head, i);
    display(head);
    delete_last_element(head);
    display(head);
}