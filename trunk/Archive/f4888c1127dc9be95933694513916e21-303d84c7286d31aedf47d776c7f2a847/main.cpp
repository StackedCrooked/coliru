bool is_ok();

#ifdef EARLY_RETURN
    
    void EarlyReturn(); // forward declaration without definition
    
    void test()
    {
        if (!is_ok())
        {
            return; // early return 
        }
        EarlyReturn();
    }

#else

    void WorkIf(); // forward declaration without definition
    
    void test()
    {
        if (is_ok())
        {
            WorkIf();
        }
    }

#endif

int main()
{
    test();
}