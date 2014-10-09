class Test
{
public:    
    virtual ~Test() {}       
};

int main()
{
    Test t;
    Test s = t; // warning: definition of implicit copy constructor for 'Test' is
                // deprecated because it has a user-declared destructor [-Wdeprecated]
}
