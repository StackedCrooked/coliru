class Test
{
public:
    Test();
    ~Test();
    
    void f()
    {
        this -> ~Test();
    }
};

int main()
{
    
    return 0;
}