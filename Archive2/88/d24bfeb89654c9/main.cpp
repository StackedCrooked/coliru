#include <memory>
#include <iostream>
#include <string.h>

int main() {
int x = 10;   //x contains value 10 
 int *ptr = &x;   // pointer ptr points to x hence ptr contains address of x, and *ptr=10 after the execution of this statement
 int &*ptr1 = ptr;   //doubt: ptr is assigned  an another alias/reference *ptr1 ? so why is this illegal
 //also the above line seems to be a reference to a pointer, then why is it a pointer to reference 
}