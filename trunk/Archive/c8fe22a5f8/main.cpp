struct Base
{
protected:
    int member;
};

struct Derived : Base
{
    void change_other(Base& p)
    {
        p.member = 42;
    }
};

int main()
{
    Derived d1{};
    Derived d2{};
    d2.change_other(d1);
}
