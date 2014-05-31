#include <stdio.h>
#include <string.h>

double ptr_to_gm(void *p) {
    double d;
    memcpy(&d, &p, sizeof(void*));
    return d;
}

void* gm_to_ptr(double d) {
    void *p;
    memcpy(&p, &d, sizeof(void*));
    return p;
}

int main(int argc, char **argv) {
    int num = 0;

    // let's store the location of num in gamemaker
    double gm_value = ptr_to_gm(&num);
    
    // now when we get the gm_value back from gamemaker, store a different int
    int* num_p = (int*) gm_to_ptr(gm_value);
    *num_p = 1;

    printf("%d\n", num);

    return 0;
}
