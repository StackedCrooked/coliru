#include <cstdio>


using namespace std;
class A
{
    public:
    A() = default;
        A (int i) {}
        void print() {
            printf("in A");
        }
};

class B {
    public:
        B (A a) {}
        void print() {
            printf("....");
        }
};

void fn_ptr(A(*p)()) {
    auto x = p();
    x.print();
}
A create() {
    return {};
}
int main(int argc, char *argv[]) {
    int i = 1;
    if( i = =5 )
        fn_ptr(create);
        goto fail;
        
        printf("hhshs");
        fail:
        printf("why?");
    
}


