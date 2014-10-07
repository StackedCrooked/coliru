//////////////  header platform.h /////////////

struct platform // singleton
{
    static platform& get() ;

    virtual ~platform() = default ;

    // public interface
    int main( /* ... */ ) ;
    void foo( /* ... */ ) ;
    void bar( /* ... */ ) ;
    // ...

    private:
        // functions to be implemented for each platform
        virtual int main_impl( /* ... */ ) = 0 ;
        virtual void foo_impl( /* ... */ ) = 0 ;
        virtual void bar_impl( /* ... */ ) = 0 ;
        // ...

        platform( const platform& ) = delete ;
        platform( platform&& ) = delete ;
        platform& operator= ( const platform& ) = delete ;
        platform& operator= ( platform&& ) = delete ;

    protected: platform() ;
};

//////////////  implementation platform.cc /////////////

//#include "platform.h"
#include <stdexcept>

namespace
{
    platform* the_platform = nullptr ;
}

platform::platform()
{
    if(the_platform) throw std::logic_error( "second instance of platform" ) ;
    the_platform = this ;
}

platform& platform::get()
{
    if( !the_platform ) throw std::logic_error( "singleton instance of platform not instantiated" ) ;
    return *the_platform ;
}

int platform::main( /* ... */ ) { return main_impl( /* ... */ ) ; }
void platform::foo( /* ... */ ) { foo_impl( /* ... */ ) ; }
void platform::bar( /* ... */ ) { bar_impl( /* ... */ ) ; }

//////////  header app_main.h
//#include "platform.h"

int app_main( /* ... */ ) ;


//////////  implementation app_main.cc ///////////////////////
//#include "app_main.h"

int app_main( /* ... */ )
{
    platform& this_platform = platform::get() ;

    this_platform.foo( /* ... */ ) ;

    int result = this_platform.main( /* ... */ ) ;

    this_platform.bar( /* ... */ ) ;

    // etc.

    return result ;
}

////////// main.cc /////////////////////////
//#include "app_main.h"
#include <iostream>

int main()
{
    try
    {
        return app_main() ;
    }
    catch( const std::exception& e )
    {
        std::cerr << "platform is not instantiated\n" ;
    }
}

////////////////// freebsd_main.cc ///////////
/////////////////  platform specific ////////////
//#include "platform.h"
#include <iostream>

namespace
{
    struct free_bsd : platform // singleton implementation for free_bsd platform
    {
        private:
            // functions to be implemented for each platform
            virtual int main_impl( /* ... */ ) override { std::cout << "free_bsd::main()\n" ; return 0 ; }
            virtual void foo_impl( /* ... */ ) override { std::cout << "free_bsd::foo()\n" ; }
            virtual void bar_impl( /* ... */ ) override { std::cout << "free_bsd::bar()\n" ; }

            // ...
    } singleton ; // instantiate singleton object
}
