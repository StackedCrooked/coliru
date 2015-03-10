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

int main()
{
    
    return 0;
}