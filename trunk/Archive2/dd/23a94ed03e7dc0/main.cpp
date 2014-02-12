//simple case
struct A {
    int a;
    char compiler_added_padding;
    int c;
};
void ex1() {
    A d = {};
    int* e = &d.a; //treating a-c as a buffer of ints
                  //but the compiler may have added padding inside
    e[0] = 1;
    e[1] = 0; //undefined behavior?
    //(I understand that e[1] is quite different from d.c)
    //http://stackoverflow.com/questions/14738407/is-it-ub-to-access-padded-bytes/14739027#14739027
    //says not undefined. OK
}

//more complex case using inheretence
//both structs 
class B {
protected:
    B() : a(), b() {}
    int a;
    short b;
    char compiler_added_padding;
};
struct C : public B {
    C() : B() {}
    short* ptr() {return &b;}
private:
    short a;
};
void ex2() {
    C f = {};
    short* g = f.ptr(); //treating a-c as a buffer of ints
                  //but the compiler may have added padding inside
    g[0] = 1;
    g[1] = 0; //undefined behavior?
}

int main() {}