class Test
{
public:    
    virtual ~Test() = default;       
};

int main()
{
    Test t;
    auto s = t; // warning: definition of implicit copy constructor for 'Test' is
                // deprecated because it has a user-declared destructor [-Wdeprecated]
}
