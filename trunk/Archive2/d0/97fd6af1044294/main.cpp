#include <stdio.h>

void fibonacci(int array[], int size) {
    int first, second, next;
    int i;
    
    first = 0;
    second = 1;
    
    for (i = 0; i < size; i++) {
        if (i <= 1)
            next = i;
        
        else {
            next = first + second;
            first = second;
            second = next;
        }
        
        array[i] = next;
    }
}

int main(int argc, char *argv[]) {
    int fib[10];
    int i;
    
    fibonacci(fib, 10);
    
    for (i = 0; i < 10; i++)
        printf("%d\n", fib[i]);
    
    return 0;    
}
