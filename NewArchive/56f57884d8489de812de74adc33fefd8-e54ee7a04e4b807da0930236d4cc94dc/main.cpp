#include <stdio.h>

struct Color{
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
};

int main(){
    
    long int color = 0x04030201;
    Color* c = (Color*)&color;

    printf(
        "r = %d\ng = %d\nb = %d\na = %d",
        c->r,
        c->g,
        c->b,
        c->a
    );
}
