#include <iostream>

class base
{
public:
    virtual void f1()
    {
        std::cout << "base::f1()" << std::endl;
    }
};

// How can I do Forward declaration for Child class ?
class child;

void show_obj( base * pb )
{
    child * pc = (child*)pb;
    pc->f1();
}


int main()
{
    child c(5);
    show_obj( &c );
    return EXIT_SUCCESS;
}

class child : public base
{
public:
    child( int a )
        : a_(a)
    {
    }

    virtual void f1()
    {
        std::cout << "child::f1()" << std::endl;
        std::cout << "a: " << a_ << std::endl;
    }
private:
    int a_;
};
