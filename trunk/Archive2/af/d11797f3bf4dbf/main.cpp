#include <stdexcept>


template <typename>
struct B;

struct A
{
    A();
    ~A();
    
    template<class> friend struct B;
    
private:
    void foo() { throw std::runtime_error("Works!"); }
    
    B<int>* b;
    A(const A&);
};

template <typename T>
struct B
{
    B(A* a) { a->foo(); }
};


A::A() : b(new B<int>(this)) {}
A::~A() { delete b; }

int main()
{
    A a;
}
