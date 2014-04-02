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

    // temp is copy constructed
    counter temp = copied ; // 6. counter object at: <address of temp> - copy constructor

    message( "return from function" ) ; // 7. return from function

    return temp ; // copy is elided (RVO)

    // 8. counter object at: <address of copied> - destructor (copied is destroyed)

    // temp is not destroyed (RVO)
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
