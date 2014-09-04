typedef int f;
namespace N
{
    struct A
    {
        friend void f(A &);
        operator int(){return 0;}
        void g(A a);
    };
    
    void f(A&);
    
    void A::g(A a)
    {
        int i = f(a);
    }
}

int main() 
{
}
