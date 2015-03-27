#include <cstdlib>

struct node
{
    int a;
    char* b;
};

int main()
{
    {
        struct node *p = (node*)malloc(sizeof(node));
        p->a = 0;      // first  element
        p->b = NULL;   // second element
        free(p);
    }
    
    {
        node* p = new node {0, NULL};
        delete p;
    }
}