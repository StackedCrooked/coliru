/****************************************************************************
* Snippets, ejemplos, y utilidades del curso de C++ orientado a videojuegos *
* https://github.com/Manu343726/CppVideojuegos/                             *
*                                                                           * 
* Copyright © 2014 Manuel Sánchez Pérez                                     *
*                                                                           *
* This program is free software. It comes without any warranty, to          *
* the extent permitted by applicable law. You can redistribute it           *
* and/or modify it under the terms of the Do What The Fuck You Want         *
* To Public License, Version 2, as published by Sam Hocevar. See            *
* http://www.wtfpl.net/  and the COPYING file for more details.             *
****************************************************************************/

#ifndef INSTANTATION_PROFILER_HPP
#define INSTANTATION_PROFILER_HPP

#define CPP_INSTPROF_EXAMPLE

#include <iostream>
#include <utility>
#include <functional>


/* Simple C++11 (move semantincs aware) instantation instrumentation utility */

namespace cpp
{
    template<typename T , bool MESSAGES = true>
    class instantation_profiler
    {
    private:
        static std::size_t _alive , _instanced , _destroyed ,
                           _ctor , _copy_ctor , _move_ctor ,
                           _copy_assign , _move_assign;

        std::size_t _id; //Si no tuviera id, se aplicaba la empty base class optimization y todos contentos, como si nada hubiera pasado.

    public:

        instantation_profiler( ) : _id( _instanced )
        {
            _alive++;
            _instanced++;
            _ctor++;

            if ( MESSAGES ) std::cout << ">> construction (ID" << _id << ")" << std::endl;
        }

        instantation_profiler( const instantation_profiler& other ) : _id( _instanced )
        {
            _alive++;
            _instanced++;
            _copy_ctor++;

            if ( MESSAGES ) std::cout << ">> copy construction (ID" << _id << " <== ID" << other.id( ) << ")" << std::endl;
        }

        instantation_profiler( instantation_profiler&& other ) : _id( _instanced )
        {
            _alive++;
            _instanced++;
            _move_ctor++;

            if ( MESSAGES ) std::cout << ">> move construction (ID" << _id << " <-- ID" << other.id( ) << ")" << std::endl;
        }

        instantation_profiler& operator=( const instantation_profiler& other )
        {
            _copy_assign++;

            if ( MESSAGES ) std::cout << ">> copy assigment ( ID" << _id << " = ID" <<  other.id( ) << ")" << std::endl;
            
            return *this;
        }

        instantation_profiler& operator=( instantation_profiler&& other )
        {
            _move_assign++;

            if ( MESSAGES ) std::cout << ">> move assigment ( ID" << _id << " = ID" <<  other.id( ) << ")" << std::endl;
            
            return *this;
        }

        ~instantation_profiler( )
        {
            _alive--;
            _destroyed++;

            if ( MESSAGES ) std::cout << ">> destruction (ID" << _id << ")" << std::endl;
        }



        std::size_t id() const
        {
            return _id;
        }

        static std::size_t alive_instances( )
        {
            return _alive;
        }

        static std::size_t instantations( )
        {
            return _instanced;
        }

        static std::size_t destructions( )
        {
            return _destroyed;
        }

        static std::size_t normal_constructions( )
        {
            return _ctor;
        }

        static std::size_t move_constructions( )
        {
            return _move_ctor;
        }

        static std::size_t copy_constructions( )
        {
            return _copy_ctor;
        }

        static std::size_t move_assigments( )
        {
            return _move_assign;
        }

        static std::size_t copy_assigments( )
        {
            return _copy_assign;
        }


        static void print_info( std::ostream& out = std::cout )
        {
            out << "# Normal constructor calls: "  << normal_constructions() << std::endl
                << "# Copy constructor calls: "    << copy_constructions()   << std::endl
                << "# Move constructor calls: "    << move_constructions()   << std::endl
                << "# Copy assigment calls: "      << copy_assigments()      << std::endl
                << "# Move assigment calls: "      << move_assigments()      << std::endl
                << "# Destructor calls: "          << destructions()         << std::endl
                << "# "                                                      << std::endl
                << "# Total instantations: "       << instantations()        << std::endl
                << "# Total destructions: "        << destructions()         << std::endl
                << "# Current alive instances: "   << alive_instances()      << std::endl;
        }
    };

    template<typename T , bool MESSAGES>
    std::size_t instantation_profiler<T,MESSAGES>::_alive       = 0;
    template<typename T , bool MESSAGES>
    std::size_t instantation_profiler<T,MESSAGES>::_instanced   = 0;
    template<typename T , bool MESSAGES>
    std::size_t instantation_profiler<T,MESSAGES>::_destroyed   = 0;
    template<typename T , bool MESSAGES>
    std::size_t instantation_profiler<T,MESSAGES>::_ctor        = 0;
    template<typename T , bool MESSAGES>
    std::size_t instantation_profiler<T,MESSAGES>::_copy_ctor   = 0;
    template<typename T , bool MESSAGES>
    std::size_t instantation_profiler<T,MESSAGES>::_move_ctor   = 0;
    template<typename T , bool MESSAGES>
    std::size_t instantation_profiler<T,MESSAGES>::_copy_assign = 0;
    template<typename T , bool MESSAGES>
    std::size_t instantation_profiler<T,MESSAGES>::_move_assign = 0;
} /* cpp namespace */


#ifdef CPP_INSTPROF_EXAMPLE

struct foo : public cpp::instantation_profiler<foo>
{
    int value;
};



//Me suena bastante que Boost tiene una biblioteca con una parida de este estilo...
struct scoped_call
{
private:
    std::function<void()> function;    

public:
    scoped_call( const std::function<void()>& f ) : function( f ) {}

    ~scoped_call()
    {
            function();
    }
};


foo f()
{
    scoped_call chapuza( [](){ std::cout << "Exiting f()..." << std::endl; } );

    std::cout << "I'm in f(), which returns a foo by value!" << std::endl;

    return foo();
}


void g1( foo )
{
    scoped_call chapuza( [](){ std::cout << "Exiting g1()..." << std::endl; } );

    std::cout << "I'm in g1(), which gets a foo by value!" << std::endl;
}

void g2( const foo& )
{
    scoped_call chapuza( [](){ std::cout << "Exiting g2()..." << std::endl; } );

    std::cout << "I'm in g2(), which gets a foo by const lvalue reference!" << std::endl;
}

void g3( foo&& )
{
    scoped_call chapuza( [](){ std::cout << "Exiting g3()..." << std::endl; } );

    std::cout << "I'm in g3(), which gets an rvalue foo reference!" << std::endl;
}

template<typename T>
void h( T&& afoo )
{
    scoped_call chapuza( [](){ std::cout << "Exiting h()..." << std::endl; } );

    std::cout << "I'm in h(), which sends a foo to g() through perfect forwarding!" << std::endl;

    g1( std::forward<T>( afoo ) );
}


//Podría haberlo escrito usando una macro, pero odio el CPP:
#define EXAMPLE( message , code ) std::cout << std::endl << message << " ( " << #code << " )" << std::endl; code


int main()
{
    std::cout << std::endl << "Just before a declaration ( foo a; )"                << std::endl;                                        foo a;
    std::cout << std::endl << "Just before b declaration ( foo b; )"                << std::endl;                                        foo b;
    std::cout << std::endl << "Just before c declaration ( foo c; )"                << std::endl;                                        foo c;
    std::cout << std::endl << "Just before d declaration ( foo d( f() ); )"         << std::endl;                                        foo d( f() );

    std::cout << std::endl << "Just before a to b assigment ( b = a )"              << std::endl;                                        b = a;
    std::cout << std::endl << "Just before ctor call to b assigment ( b = foo() )"  << std::endl;                                        b = foo();
    std::cout << std::endl << "Just before f() call to b assigment ( b = f() )"     << std::endl;                                        b = f();



    std::cout << std::endl << "Just before g1( foo ) call with lvalue arg ( g1( a ) )"                         << std::endl;             g1( a );
    std::cout << std::endl << "Just before g1( foo ) call with rvalue arg ( g1( f() ) )"                       << std::endl;             g1( f() );
    std::cout << std::endl << "Just before g1( foo ) call with lvalue ==> rvalue arg ( g1( std::move( a ) ) )" << std::endl;             g1( std::move( a ) );

    std::cout << std::endl << "Just before g2( const foo& ) call with lvalue arg ( g2( b ) )"                          << std::endl;     g2( b );
    std::cout << std::endl << "Just before g2( const foo& ) call with rvalue arg ( g2( f() ) )"                        << std::endl;     g2( f() );
    std::cout << std::endl << "Just before g2( const foo& ) call with lvalue ==> rvalue arg ( g2( std::move( b ) ) )"  << std::endl;     g2( std::move( b ) );

  //std::cout << std::endl << "Just before g3( foo&& ) call with lvalue arg ( g3( c ) )"                         << std::endl;           g3( c ); (Por supuesto no tiene sentido. Lo pongo por coherencia)
    std::cout << std::endl << "Just before g3( foo&& ) call with rvalue arg ( g3( f() ) )"                       << std::endl;           g3( f() );
    std::cout << std::endl << "Just before g3( foo&& ) call with lvalue ==> rvalue arg ( g3( std::move( c ) ) )" << std::endl;           g3( std::move( c ) );



    std::cout << std::endl << "Just before h() call with lvalue arg ( h( d ) )"                         << std::endl;                    h( d );
    std::cout << std::endl << "Just before h() call with rvalue arg ( h( f() ) )"                       << std::endl;                    h( f() );
    std::cout << std::endl << "Just before h() call with lvalue ==> rvalue arg ( h( std::move( d ) ) )" << std::endl;                    h( std::move( d ) );

    foo::print_info( std::cout );
}

#endif /* CPP_INSTPROF_EXAMPLE */
#endif /* INSTANTATION_PROFILER_HPP */