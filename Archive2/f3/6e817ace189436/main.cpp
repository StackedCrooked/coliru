struct Node
{
    int value;
    Node* next;
};

typedef Node* List;

List tail(List lst) { return lst ? lst->next : nullptr; }
List prepend(List head, List lst) { head->next = lst; return head; }

List reverse(List lst, List revLst = nullptr)
{
    List lstTail = tail(lst); // C++ evaluates arguments in undefined order
    return lst ? reverse(lstTail, prepend(lst, revLst)) : revLst;
}

// ---------------

List cons(int value, List tail) { return new Node{value, tail}; }
int head(List lst) { return lst->value; }

#include <cstdio>

void print(List lst) { if (lst) { printf("%d\n", head(lst)); print(tail(lst)); } }

int main()
{
    List lst = cons(1, cons(2, cons(3, nullptr)));
    print(lst);
    printf("----\n");
    List revLst = reverse(lst);
    print(revLst);
}