class A
{
private:
    int i;
};

class B : public A
{
public:
    void foo() { i = 2; }
};

int main()
{
    B b;
};