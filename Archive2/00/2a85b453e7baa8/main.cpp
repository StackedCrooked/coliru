class myClass
{
    int function1();
    int function2();
    
    class A_t
    {
        int A;
        A_t& operator=(int p) { A = p; return *this; }
        A_t(int p) : A(p) {}
    public:
        A_t() = default;
        operator int() { return A; }
        
    friend int myClass::function1();
    };
    
    A_t A;
};

int myClass::function1()
{
    A = 42;
    return A;
}

int myClass::function2()
{
    A = 42;
    return A;
}

int main() {}