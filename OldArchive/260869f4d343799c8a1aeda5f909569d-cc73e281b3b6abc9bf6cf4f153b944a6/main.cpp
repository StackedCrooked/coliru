struct A{
    A(int) {}
    operator int() {return 0;}
};

void foo(A, A) {}
void foo(int, int) {}

int main() {
    A a = 3;
    foo(a, 4); //error: call of overloaded ‘foo(A&, int)’ is ambiguous
}