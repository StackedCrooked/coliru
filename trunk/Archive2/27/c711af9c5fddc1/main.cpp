class myClass
{
    int function1();
    int function2();
    
    struct A_t
    {
        int A;
        A_t& operator=(int p) { A = p; return *this; }
    public:
        A_t() = default;
        A_t(int p) : A(p) {}
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