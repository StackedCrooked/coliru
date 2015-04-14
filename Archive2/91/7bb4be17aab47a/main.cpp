class TheClass
{
public:
    template<typename T>
    int doSomething(T thing);
};

template<typename T>
int TheClass::doSomething(T thing)
{
    return 42;
}

int main()
{
    TheClass c;
    c.doSomething(17);
}