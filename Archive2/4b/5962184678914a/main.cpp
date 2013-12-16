#include <stdio.h>

#define unused __attribute__((unused))

#define foo(a) puts("Macro")

//Replace below function for error
//void foo(unused int i) {
//    puts("Function");
//}

//Putting parentheses around foo stops macro expansion
void (foo)(unused int i) {
    puts("Function");
}

int main() {
    (foo)(1); //parentheses: no expansion -> function
    foo(1); //no parentheses: expansion -> macro
}
