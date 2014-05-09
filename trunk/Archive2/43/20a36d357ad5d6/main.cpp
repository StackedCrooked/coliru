struct outer
{
    void f(bool = true) {}
    void a();
    
    struct inner
    {
        friend void outer::f(bool);
    };
};

void outer::a()
{
    f();
}

int main()
{
    outer().a();
}



