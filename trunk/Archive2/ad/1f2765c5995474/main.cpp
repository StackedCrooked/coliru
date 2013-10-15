struct A {
    A() {}
    A(int) {}
};

int main()
{
    A a1();
    A a2(1);
    a1 = a2;
}