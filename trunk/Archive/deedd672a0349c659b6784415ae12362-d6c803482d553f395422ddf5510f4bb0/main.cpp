#include <iostream>
#include <string>
#include <vector>

struct Z {
    struct A * a;
    struct B * b_list;
}

void init(struct Z z) {
    create_a(*&Z.a);
    
    create_b(&Z.b_list); // this doesn't get me anything.
}

int create_a(struct A * a) {
    // do things;
}

int create_b(struct B ** b_list) {
    // do things;
}