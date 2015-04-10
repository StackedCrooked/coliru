#include <stdexcept>
#include <iostream>

namespace bad // non-virtual inheritance from exception base class
{
    struct file_open_error : std::runtime_error
    { file_open_error() : std::runtime_error( "failed to open file" ) {} };

    struct network_error : std::runtime_error
    { network_error() : std::runtime_error( "unable to access network" ) {} };

    void foo()
    {
        // try to open file on a network server; on failure
        {
            struct network_file_error final : file_open_error, network_error
            { network_file_error() {} };

            throw network_file_error() ;
        }
    }
}

namespace good // virtual inheritance from exception base class
{
    struct file_open_error : virtual std::runtime_error
    { file_open_error() : std::runtime_error( "failed to open file" ) {} };

    struct network_error: virtual std::runtime_error
    { network_error() : std::runtime_error( "unable to access network" ) {} };

    void foo()
    {
        // try to open file on a network server; on failure
        {
            struct network_file_error final : file_open_error, network_error
            { network_file_error() : std::runtime_error( "unable to access network => failed to open file" ) {} };

            throw network_file_error() ;
        }
    }
}

int main()
{
    try { std::cout << "this (non-virtual inheritance from exception base class) is bad:\n  " ; bad::foo() ; }

    catch( const std::exception& e ) // won't be caught here: ambiguous conversion to std::exception
    { std::cout << "caught std::exception what: '" << e.what() << "'\n" ; }

    catch(...) // but caught here
    { std::cout << "caught some unknown error\n" ; }

    std::cout << "------------------------------\n" ;

    try { std::cout << "this (virtual inheritance from exception base class) is what we want:\n  " ; good::foo() ; }

    catch( const std::exception& e ) // will be caught here: unambiguous conversion to std::exception
    { std::cout << "caught std::exception what: '" << e.what() << "'\n" ; }

    catch(...)
    { std::cout << "caught some unknown error\n" ; }
}
