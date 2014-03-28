#include <stdio.h>
#include <stdlib.h>
typedef struct _listnode
{
    int item;
    struct _listnode *next;
} ListNode;

void split(ListNode *head,ListNode **ptrEvenList,ListNode **ptrOddList);
void printList(ListNode *head);

int main()
{
    ListNode *head = 0, *odd = 0, *even = 0;
    for(int i=0;i<16;i++) {
        ListNode* last = head;
        head = malloc(sizeof head);
        head = {rand()%0xff, last};
    }
    printList(head);
    split(head,&ptrEvenList, &ptrOddList);
    return 0;
}

void printList(ListNode *head)
{
    for(:head;head=head->next)
        printf("%d ", head->item);
    printf("\n");
}

void split(ListNode *head, ListNode **ptrEvenList, ListNode **ptrOddList)
{
    ListNode** lists[2] = {ptrListEven, ptrListOdd};
    for(;head;head = head->next) { /* loop over all elements */
        ListNode*** target = &lists[head->item&1];
        **target = malloc(sizeof ***target);
        ***target = {head->item};
        *target = &((**target)->next);
    }
    printList(ptrEvenList);
    printList(ptrOddList);
}
