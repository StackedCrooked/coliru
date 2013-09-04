#include <stdio.h>
#include <stdlib.h>

static inline int sum(int a, int b) {
  return (a + b);
}

int main()
{
    int c = sum(1, 4);
    // If the compiler inlines the function the compiled 
    // code will be the same as writing: int c = 1 + 4;
    
    printf("Result: %d\n", c);

    return EXIT_SUCCESS;
}