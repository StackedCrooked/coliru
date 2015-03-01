#include <stdio.h>

int main(){
    unsigned i, j, a[10] = {0};

    for (j = 23; j < 25; j++){
        for (i = j / 8; i --> 0;) a[i] = 0;
        for (i =     1; i --> 0;) printf("%u", a[i]);
    }

    return 0;
}
