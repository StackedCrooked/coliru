#include <stdio.h>

#define MAX_SZ 256

typedef struct Pair_ {
    char key[32];
    char meaning[MAX_SZ];
} Pair;

int main()
{
    const Pair entries[] = {
        "gmg", "google mo gago"
    };
    
    printf("%s : %s", entries[0].key, entries[0].meaning);
    
    return 0;   
}