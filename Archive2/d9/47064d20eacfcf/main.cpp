// Problem: reverse last n elements in a slist

#include <memory>
#include <iostream>

using namespace std;

//----------------------------------------------------------------------------->
// Helper functions
//----------------------------------------------------------------------------->

// Reverse the enitre slist 
template <typename List> void reverse(List& phead)
{
    List pcur = move(phead);
    phead = nullptr;

    while (pcur != nullptr)
    {
        List pnewcur = move(pcur->pnext);
        pcur->pnext = move(phead);
        phead = move(pcur);
        pcur = move(pnewcur);
    }
}

// Traverse n elements forward or to the end of the slist, whichever happens earlier
template <typename List> List& advance(List& phead, unsigned int n)
{
    List *ppn = &phead;
    for (unsigned int i = 0; *ppn != nullptr && i < n; ++i, ppn = &(*ppn)->pnext);
    return *ppn;
} 

//----------------------------------------------------------------------------->
// Solution
//----------------------------------------------------------------------------->

template <typename List> void reverse_last_n(List& phead, unsigned int n)
{
    List *pp = &phead;
    for (List *ppn = &advance(*pp, n); *ppn != nullptr; pp = &(*pp)->pnext, ppn = &(*ppn)->pnext);
    reverse(*pp);
}

//----------------------------------------------------------------------------->
// Test
//----------------------------------------------------------------------------->

// Print a slist
template <typename List> void print(const List& phead)
{
    const List *pp = &phead;

    while ((*pp) != nullptr)
    {
        cout << (*pp)->value;
        pp = &(*pp)->pnext;
    }
    
    cout << ".\n";
}

// Node of a slist chained by naked pointers
struct node
{
    int value;
    node *pnext;
    
    node(int init_value, node *init_pnext) :
        value(init_value),
        pnext(init_pnext)
    {}
};

// Node of a slist chained by smart pointers
struct unode
{
    int value;
    unique_ptr<unode> pnext;
    
    unode(int init_value, unique_ptr<unode> init_pnext) :
        value(init_value),
        pnext(move(init_pnext))
    {}
};

// Standard make_unique appears only in C++14
template <typename T, typename... Args> unique_ptr<T> make_unique(Args&&... args)
{
    return unique_ptr<T>(new T(forward<Args>(args)...));
}

int main()
{
    cout << "Test the solution on slist chained by naked pointers\n";

    node *slist = new node(1, new node(2, new node(3, new node(4, new node(5, new node(6, nullptr))))));

    print(slist);
    reverse_last_n(slist, 5);
    print(slist);

    cout << "Test the solution on slist chained by smart pointers\n";

    unique_ptr<unode> slist_via_uptr = make_unique<unode>(1, make_unique<unode>(2, make_unique<unode>(3, make_unique<unode>(4, make_unique<unode>(5, make_unique<unode>(6, nullptr))))));

    print(slist_via_uptr);
    reverse_last_n(slist_via_uptr, 5);
    print(slist_via_uptr);
}
