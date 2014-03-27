#include <stdio.h>
 
int main()
{
    FILE* f = fopen("non_existent", "r");
    if (f == NULL) {
        perror("open()");
    } else {
        fclose(f);
    }
}