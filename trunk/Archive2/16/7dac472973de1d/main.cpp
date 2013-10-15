template<class T>
struct Base
{
    void foo() {}
};

template<class T>
struct Derived : Base<T>
{
    // comment this line out and see what happens
    using Base<T>::foo;
    
    void bar() { foo(); }
};

int main()
{
    Derived<int>().bar();
}