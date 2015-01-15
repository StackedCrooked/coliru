#include <iostream>

void bar() {}
void foo(){}
void baz() {}
void roomba() {}

int main()
{
    int val = 2 ;

 switch(val) {
    case 0:
        foo();
        break;
    case 1:
        bar();
        // oops
    case 2:
        baz();
        break;
    default:
        roomba();
}
    return 0;
}