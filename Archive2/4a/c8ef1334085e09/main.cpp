#include <stdio.h>
#include <utility>

struct X{
    int i;
    void transform(){}
    X() :i(0){puts("default");}
    X(const X& src): i(src.i){puts("copy");}
    X(X&& msrc) :i(msrc.i){puts("move");}
};

X getTransform(const X& src){
    X tx(src);
    tx.transform();
    return tx;
}

int main(){
    X x1;// default
    puts("");
    X x2(x1); // copy
    puts("");
    X x3{static_cast<X&&>(X{})}; // default then move
    puts("");
    X x41(getTransform(x2)); // copy in function ,then what?
    puts("");
    X x42(static_cast<X&&>(getTransform(x2))); // copy in funciton, then move
    puts("");
    X x51( (X()) );//default, then move? or copy? // extra() for the most vexing problem
    puts("");
    X x52(static_cast<X&&>(X())); //default then move
}