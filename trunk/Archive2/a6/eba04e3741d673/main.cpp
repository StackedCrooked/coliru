template<typename T>
struct A
{
    void f() { using type = typename T::type; }
    
    void g() { f(); }    
};

int main()
{
    A<int> a;
}