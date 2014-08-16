#include <iostream>
#include <string>
#include <vector>

class A
{
    // these functions are in the lexical scope of the class
    public: friend int foo( A& a ) { std::cout << "foo in lexical scope of A\n" ; return ++a.i ; }
    private: friend int bar( A& a ) { std::cout << "bar in lexical scope of A\n" ; return ++a.i ; }
    
    // foobar in not the lexical scope of the class
    // it is in the same scope that the class appears in
    // in this case, at the global namespace scope
    private: friend int foobar( A& a ) ;
    
    private: int i = 0 ;
};

namespace B { class C ; }
int bazbar( B::C & c ) ;

namespace B
{
    class C
    {
        // these functions are in the lexical scope of the class
        public: friend int foo( C & c ) { std::cout << "foo in lexical scope of B::C\n" ; return ++c.i ; }
        public: friend int bar( C& c ) { std::cout << "bar in lexical scope of B::C\n" ; return ++c.i ; }
        
       // foobar in not the lexical scope of the class
       // here, it is in namespace B
        private: friend int foobar( B::C& c ) ;
        
       // bazbar in not the lexical scope of the class
       // it is in the global namespace
        private: friend int ::bazbar( B::C& c ) ;

        private: int i = 0 ;
    };
}

int foobar(A& a ) { std::cout << "foobar in the global unnamed namespace\n" ; return ++a.i ; }
int B::foobar( B::C & c ) { std::cout << "foobar in namespace B\n" ; return ++c.i ; }
int bazbar( B::C & c ) { std::cout << "bazbar in the global unnamed namespace\n" ; return ++c.i ; }

int main()
{
    A a ;

    //A::foo(a) ; // **** error: 'foo' is not a member of 'A'
    // ::foo(a) ; // *** error: there is no foo in the global namespace
    // foo is not a member of A, but it is within the lexical scope of A

    foo(a) ; // argument dependant look up 
    bar(a) ; // argument dependant look up
    
    foobar(a) ; // unqualified name lookup
    ::foobar(a) ; 
    
    B::C c ;
    
    foo(c) ; // argument dependant look up
    bar(c) ; // argument dependant look up
    
    foobar(c) ; // argument dependant look up
    ::B::foobar(c) ;  
    
    bazbar(c) ; // unqualified name lookup
    ::bazbar(c) ;
}
