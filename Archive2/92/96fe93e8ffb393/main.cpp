#include <memory>
#include <iostream>
using namespace std;

template<typename T, void f(T *)>
struct func_deleter {
    void operator()(T *p) const {
        f(p);
    }
};

void mydeleterfunc(int *p) { 
    std::cout << "Sto deletando\n";
    delete p;
}

using my_ptr = std::unique_ptr<int, func_deleter<int, mydeleterfunc>>;


// new stuff using a trampoline

template<typename T>
void mydeleterfunc_t(void *p) 
{ 
    delete static_cast<T*>(p);
}

template<void f(void*)>
struct func_deleter_void {
    void operator()(void *p) const {
        f(p);
    }
};

struct Base
{
    virtual void foo() { cout << "base" << endl; }
};

struct Derived : Base
{
    ~Derived() { cout << "morendo" << endl; }
    void foo() override { cout << "derived" << endl; }
};

using my_ptr_void = 
    std::unique_ptr<Base, func_deleter_void<mydeleterfunc_t<Derived>>>;

int main()
{
   my_ptr_void ptr { new Derived{} };
   cout << sizeof(my_ptr_void) << endl;
}
