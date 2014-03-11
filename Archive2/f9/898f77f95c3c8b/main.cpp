namespace name
{
    class test
    {
    public:
        enum flag
        {
            firstflag = 1, secondflag = 2, thirdflag = 4
        };

        void foo(flag flags)
        {
            return;
        }
    };
}

int main(int argc, char *argv[])
{
    using name::test;
    
    test obj;

    obj.foo((test::flag)(test::firstflag | test::secondflag));

    return 0;
}