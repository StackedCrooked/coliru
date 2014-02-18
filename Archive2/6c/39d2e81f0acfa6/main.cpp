struct foo
{
    void bar() {}
    void bar1() & {}
    void bar2() && {}
};

int main()
{
    foo().bar();  // (always fine)
    foo().bar1(); // doesn't compile because bar1() requires an lvalue
    foo().bar2();
    
    foo f;
    f.bar();      // (always fine)
    f.bar1();
    f.bar2();     // doesn't compile because bar2() requires an rvalue
}
