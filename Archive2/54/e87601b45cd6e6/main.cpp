struct A{
    operator char() const{ return 'a'; }
    operator int() const{ return 10; }
};

struct B {
    void operator<< (int) { }
    void operator<< (long) { }
};

int main()
{
    A a;
    B b;
    b << a;
}