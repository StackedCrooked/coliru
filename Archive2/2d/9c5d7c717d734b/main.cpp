

long aaa();
void bbb();


#if A
    
    void test()
    {
        if (__builtin_expect(aaa(), 0))
        {
            bbb();
        }
    }
    

#elif B
    
    void test()
    {
        if (aaa())
        {
            bbb();
        }
    }
    
#endif

