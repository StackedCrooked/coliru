#include <iostream>

struct A
{
    void mem_fun_display() const ;
    void mem_fun_display2() const ;
    int v ;
};

void free_fun_display( const A* This )
{
    // 'This' is the parameter that is explicitly passed to the function
    // 'This' is a pointer which points to the object to be displayed
    std::cout << "free_fun_display() is called to display the object "
               << "at address    " << This << "  A{"
               << This->v // member 'v' of object pointed to by 'This'
               << "}\n" ;
}

void A::mem_fun_display() const
{
    // 'this' is a keyword; used to access a parameter that is inplicitly passed
    // 'this' is a pointer which points to the object to be displayed
    const A* This = this ;
    std::cout << "A::mem_fun_display() is called to display the object "
               << "at address  " << This << "  A{"
               << This->v // member 'v' of object pointed to by 'This'
               << "}\n" ;
}

void A::mem_fun_display2() const
{
    std::cout << "A::mem_fun_display2() is called to display the object "
               << "at address " << this << "  A{"
               << v // this->v (member 'v' of object pointed to by 'this')
               << "}\n" ;
}

int main()
{
    A a {100 } ;

    free_fun_display( &a ) ;
    a.mem_fun_display() ;
    a.mem_fun_display2() ;

    // free_fun_display() ; // ***error: pointer to an object is required
    // A::mem_fun_display() ; // ***error: object is required
}
