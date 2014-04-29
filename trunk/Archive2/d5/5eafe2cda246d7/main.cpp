struct foo
{
    foo(int);
    foo();
};

foo::foo(int) {}
foo::foo()
{
    this->foo::foo(42);
}

int main()
{
    foo f;
}