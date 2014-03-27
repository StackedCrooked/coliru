#include <iostream>
using namespace std;

int main(void)
{
    int a1 = 40;
    int* b1 = &a1;
    char* c1 = (char *)(b1);
    *c1 = 'A';
    int *t = (int*)c1;


    cout << a1 << " " << *t << endl;
    cout << &a1 << " " << t << endl; 

    return 0;
}