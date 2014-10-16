class Base
{
public:
    void DoSomething(){}    
};

void DoSomething(int){}

template <class T>
void Func(T t)
{
    DoSomething(t);    
}

int main()
{
    int a = 1;
    Func(a);
    
    Base b;
    Func(b);
}
