constexpr auto foo()
{
    while(true);
    return true;
}

int main()
{
    constexpr auto x = foo();
}