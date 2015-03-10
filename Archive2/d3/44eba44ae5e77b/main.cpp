class Test
{
public:
    Test();
    ~Test();
    
    void f()
    {
        ~Test();
    }
};