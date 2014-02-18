
struct foo
{
    void bar() {}
    void bar1() & {}
    void bar2() && {}
};

int main()
{
    foo().bar();
    foo().bar1(); // doesn't compile because bar1() object is an lvalue
    foo().bar2();
    
    foo f;
    f.bar();
    f.bar1();
    f.bar2();     // doesn't compile because bar1() object is an rvalue
}
