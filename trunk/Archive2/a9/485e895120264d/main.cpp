#include "a.h"
void doSomething();

int a = -1; //Defining external int. Single point of definition

int main() {
    a = 10;
    doSomething();
    return 0;
}