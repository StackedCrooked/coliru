bool is_ok();

#ifdef EARLY_RETURN
    
    void TestEarlyReturn(); // forward declaration without definition
    
    void test()
    {
        if (!is_ok())
        {
            return; // early return 
        }
        TestEarlyReturn();
    }

#else

    void TestNoEarlyReturn(); // forward declaration without definition
    
    void test()
    {
        if (is_ok())
        {
            TestNoEarlyReturn();
        }
    }

#endif

int main()
{
    test();
}