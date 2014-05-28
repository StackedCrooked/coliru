#include <iostream>

struct A
{
    typedef void (*Fun)(A*);
    
    A() : fun(do_work) {}
    
    void work()
    {
        fun(this);
    }
    
    // set the work function
    // returns the old one
    Fun set_fun(Fun new_fun)
    {
        auto old = fun;
        fun = new_fun;
        return old;
    }
    
private:
    // the default work function
    static void do_work(A*)
    {
        std::cout << "Worky worky." << std::endl;
    }
    
    Fun fun;
};



A::Fun old_fun;

void hook(A* a)
{
    std::cout << "Hookie hookie." << std::endl;
    old_fun(a);
    std::cout << "/hookie" << std::endl;
    
}

int main()
{
    A a;
    old_fun = a.set_fun(hook);
    a.work();
}
