void func()
{
    struct Test
    {
        int f();
    };
    //return Test{};
}

using func_Test = decltype(func());

int func_Test::f()
{
    return 7;
}
