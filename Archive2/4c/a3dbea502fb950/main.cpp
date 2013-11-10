auto foo(int, double)
{
    if(false) return 42;
    
    decltype( foo(0, 1.2) ) x;
    x = 42;
    return x;
}

int main()
{
    auto x = foo(42, 1.2);
    (void)x;
}
