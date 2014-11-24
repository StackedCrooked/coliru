struct foo
{
    foo(){}
    
    int a;
    foo& operator=(foo&)
    {
        a=12;
        return *this;
    }
};

int main()
{
    const foo a;
    foo b;
    //b = a;      //statement A
    b = foo();    //Statement B
}
