    struct Base
    {
        int i;
        virtual int get() const { return 5; }
        
        Base() : i() {}
        Base(Base const& p)
        {
            i = p.get() * 2;
        }
    };
    struct Derived : Base
    {
        virtual int get() const { return 10; }
    };
    
    
    #include <iostream>
    
    int main()
    {
        Base b = Derived();
        std::cout << b.i;
    }