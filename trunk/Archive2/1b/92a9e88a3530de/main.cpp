#include <iostream>
#include <iomanip>

struct node
{
    node(int data, node* next = nullptr)
        : data(data)
        , next(next)
    { }
    int data;
    node* next;
};

void push(node*& head, int value)
{
    node** curr = &head;
    while (cur[0]->next)
        cur = &cur[0]->next;
    cur->next = new node(value);
}

void push(node*& head, std::initializer_list<int> v)
{
    for (auto& c : v)
        push(head, c);
}

void display(node* head)
{
    while (head)
    {
        std::cout << head->data << " ";
        head = head->next;
    }
    std::cout << '\n';
}

void insertSorted(node*& head, int value)
{
    node** cur = &head;
    while (cur[0] && cur[0]->value < value)
        cur = &cur[0]->next;
        
    if (cur[0])
    {
        cur[0] = new node(value, cur[0]->next;
    }
}

int main()
{
    
}