#include <iostream>
#include <sstream>

void message( const std::string& msg )
{
    static int n = 0 ;
    std::cout << ++n << ". " << msg << '\n' ;
}

struct counter
{
    counter() { message( This() + "default constructor" ) ; };
    counter( const counter& ) { message( This() + "copy constructor" ) ; }
    counter( counter&& ) { message( This() + "move constructor" ) ; }
    ~counter() { message( This() + "destructor" ) ; }

    std::string This() const
    {
        std::ostringstream stm ;
        stm << "counter object at: " << this << " - " ;
        return stm.str() ;
    }
};

// copied is copy constructed when the function is called
counter copy( counter copied ) // 4. counter object at: <address of copied> - copy constructor
{
    message( "entered function" ) ; // 5. entered function

    message( "return from function" ) ; // 6. return from function

    return copied ;

    // The IS expressly prohibits copy elision (if there is an observable side effect)
    // for a function (or catch-clause) parameter.
    // destructor of copied has to be called before the function returns.

    // move the function parameter to the anonymous return value
    // which is at the memory set aside for two in main (RVO)
    // destructor of copied has a side effect, it has to to be called

    // 7. counter object at: <memory for two in main> - move constructor
    // 8. counter object at: <address of copied> - destructor (copied is destroyed)
}

int main()
{
    message( "creating one" ); // 1. creating one
	counter one; // 2. counter object at: <address of one> - default constructor

	message( "calling function" ); // 3. calling function

	counter two = copy(one); // copy of returned prvalue is elided (RVO)

	message( "back in main" ); // 9. back in main

	message( "returning from main" ) ; // 10. returning from main

	// two and one are destroyed
	// 11. counter object at: <address of two> - destructor
	// 12. counter object at: <address of one> - destructor
}
