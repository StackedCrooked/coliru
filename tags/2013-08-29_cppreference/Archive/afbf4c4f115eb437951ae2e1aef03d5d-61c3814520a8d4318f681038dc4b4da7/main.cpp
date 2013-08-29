template<class D>
struct base{
    template<class>
    void f(){}
};

template<class T>
struct derived : base<derived<T>>{
    using my_base = base<derived<T>>;
    
private:
    using my_base::f;
};

int main()
{
    derived<int> d;
    d.f<int>();
}