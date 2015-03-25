#include <iostream>

struct singly_linked_list_elem
{
  singly_linked_list_elem * next;
  int payload;
};

struct singly_linked_list
{
    singly_linked_list(int first_payload);
    void append(int payload);
    void print();
    singly_linked_list_elem * head;
    singly_linked_list_elem * tail;
};

singly_linked_list::singly_linked_list(int first_payload) 
{
    singly_linked_list_elem * new_elem = new singly_linked_list_elem();
    new_elem->payload = first_payload;
    new_elem->next = nullptr;
    head = new_elem;
    tail = new_elem;
}

void singly_linked_list::append(int payload)
{
    singly_linked_list_elem * new_elem = new singly_linked_list_elem();
    new_elem->payload = payload;
    new_elem->next = nullptr;
    tail->next = new_elem;
    tail = new_elem;
}

void singly_linked_list::print()
{
    singly_linked_list_elem * cur_elem = head;
    while( cur_elem )
    {
        printf( "%d ", cur_elem->payload);
        cur_elem = cur_elem->next;
    }
}

void print_reversed( singly_linked_list_elem * cur_elem )
{
    if (cur_elem) // branch prediction friendly
    {
       print_reversed(cur_elem->next);
       printf( "%d ", cur_elem->payload );
    }
}

int main()
{
    singly_linked_list l(1);
    l.append(2);
    l.append(3);
    l.print();
    print_reversed(l.head);
}
