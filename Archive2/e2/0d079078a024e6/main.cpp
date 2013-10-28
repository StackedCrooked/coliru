template<typename T>
struct A
{
    void f() { using type = typename T::type; }
    
    virtual void g() { f(); }    
};

int main()
{
    A<int> a;
}