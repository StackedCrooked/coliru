class A
{
    public:
    void doStuff( A& targetA )
    {
        targetA.m_elem = 4;
    }
    
protected:
    int m_elem;
}


int main()
{
    A meA;
A targetA;


    meA.doStuff( targetA );
}