struct A {};
A a;
struct B : A {
    B(): decltype(a)() {}
};
int main() {}
