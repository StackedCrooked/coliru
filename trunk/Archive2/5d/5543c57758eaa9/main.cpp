#include <stdio.h>

int main(void) {
    int letters[] = {['A'] = 4, ['B'] = 8, ['E'] = 3, ['I'] = 1, ['O'] = 0, ['S'] = 5};   
    
    for (int i = 0; i < 'S'; ++i) {
        printf("%d ", letters[i]);
    }
}
