struct A
{
    virtual void copy(A& a) {}
};

struct B : public A
{
    virtual void copy(B& b) override {}
};

int main()
{
    B b;
    b b2;
    b.copy(b2);
    
    return 0;
};