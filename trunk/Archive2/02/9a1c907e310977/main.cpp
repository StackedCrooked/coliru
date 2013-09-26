#include <stdlib.h>
 
int main(int argc, char* argv[]) 
{
    int* ptr = (int*) malloc(sizeof(int));
    free(ptr);
    return 0;
}