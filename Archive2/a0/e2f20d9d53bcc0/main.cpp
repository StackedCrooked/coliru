#include <stdio.h>
#include <stdlib.h>
 
struct A {
int a;
int b;
};
 
void* p;
 
int* availableStackFrameAddr() {
int a;
return &a;
}
void foo() {
A a;
p = &a;
printf("%p\n", availableStackFrameAddr());
}
void bar() {
A a;
p = &a;
a.a = 1;
printf("%p %d\n", availableStackFrameAddr(), a.a);
}
void baz() {
A a;
p = &a;
a.b = 2;
printf("%p %d\n", availableStackFrameAddr(), a.b);
}
void bazz() {
A a;
p = &a;
a.a = 11;
a.b = 22;
printf("%p %d %d\n", availableStackFrameAddr(), a.a, a.b);
}
int main() {
printf("%p\n", availableStackFrameAddr());
foo();
bar();
baz();
bazz();
return EXIT_SUCCESS;
}