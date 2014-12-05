struct M
{
    virtual ~M() = default;    
    virtual M* foo() = 0;
};

struct M1 : M
{
    virtual M1* foo() override { return nullptr; }
};

int main() {}
