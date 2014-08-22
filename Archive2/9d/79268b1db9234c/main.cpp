class X
{
public:
    void foo(int) { }    // #1
private:
    void foo(double) { } // #2
};

int main()
{
    X x;
    x.foo(0.0);
}