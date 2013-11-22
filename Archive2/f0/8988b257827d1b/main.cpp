class A 
{
    public: 
    
        // declare a non-default contructor and by doing so instruct the compiler that 
        // you don't won't the default constructor defined.
        A(int b);
        
        // If we declare the non-default construcotr above we must also declare the default one
        // Uncomment the line below to fix compiler errors
        // A();
        
    private:
    int b;
    
};

// Define a default constructor
// Uncomment the line below to fix compiler errors
//A::A() {}

A::A(int b) : b(b) {}





int main()
{
    // try to invoke default constructor
    // oops, error, since we defined a non default one, we don't automatically get an automatic one created by the compiler
    A a;
    
    // invoke non-default constructor. This works
    A a1(1);
}
