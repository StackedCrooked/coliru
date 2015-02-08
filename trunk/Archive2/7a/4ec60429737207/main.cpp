#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#define STACKSIZE 100
 
// stack structure
struct stack
{
    int top;
    int items[STACKSIZE];
};
 
// Stack Functions to be used by printNGE()
void push(struct stack *ps, int x)
{
    if (ps->top == STACKSIZE-1)
    {
        printf("Error: stack overflow\n");
        getchar();
        exit(0);
    }
    else
    {
        ps->top += 1;
        int top = ps->top;
        ps->items [top] = x;
    }
}
 
bool isEmpty(struct stack *ps)
{
    return (ps->top == -1)? true : false;
}
 
int pop(struct stack *ps)
{
    int temp;
    if (ps->top == -1)
    {
        printf("Error: stack underflow \n");
        getchar();
        exit(0);
    }
    else
    {
        int top = ps->top;
        temp = ps->items [top];
        ps->top -= 1;
        return temp;
    }
}

void f(struct stack* s1, struct stack* s2)
{
   // if(!isEmpty(s1))
    {
        //push(s2, pop(s1));
        //f(s1,s2);
    }
}
 
/* Driver program to test above functions */
int main()
{
    struct stack s1;
    s1.top=-1;
    push(&s1, 1);
    push(&s1, 2);
    push(&s1, 3);
    
    struct stack s2;
    s2.top=-1;
    f(&s1,&s2);
    
    while(!isEmpty(&s1))
    {
        std::cout << isEmpty(&s2) << std::endl;
    }
    
    getchar();
    return 0;
}
