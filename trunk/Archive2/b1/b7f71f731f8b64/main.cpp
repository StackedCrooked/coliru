#include <stdio.h>

main(){
    union test{char *id;char *name;};
    union test me;
    me.id ="hello";
    printf("\n%s",me.id);
    printf("\n%s",me.name);
} 