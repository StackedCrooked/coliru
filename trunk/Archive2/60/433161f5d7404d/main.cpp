struct S
{
    int& foo() { return i; }
    int i = 0;
};

int main()
{
    int i = 0;
    [=] () { return &i; }();
    
    S().foo();
}
