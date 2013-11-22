struct X {
    explicit X(int) {}  
};

int main()
{
    X x1(42); // ok
    // this is an error:
    // X x2 = 42;
}