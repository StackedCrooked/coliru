struct A {
    int a;
    char compiler_added_padding;
    int c;
};

int main() {
    A d;
    int* e = d.a; //treating a-c as a buffer of ints
                  //but the compiler may have added padding inside
    e[0] = 1;
    e[1] = 0; //undefined behavior?
    return e[1]; //undefined behavior?
}