#include <iostream>
#include <string>

// =================================
// print_attribs parameter usage : ( os, name0, val0, ..., nameN, valN )
// name is char const* or std::string
// val can be anything compatible with os operator<<
// print_attribs is specialize for char const* and std::string values to enclose them with double quotes.

template < typename T, typename... Ts> void print_attribs( std::ostream & os, char const * name, T&& val, Ts&&... ts );
template < typename... Ts>             void print_attribs( std::ostream & os, char const * name, char const * val, Ts&&... ts );
template < typename... Ts>             void print_attribs( std::ostream & os, char const * name, std::string const & val, Ts&&... ts );

template < typename T, typename... Ts> void print_attribs( std::ostream & os, std::string const & name, T&& val, Ts&&... ts );
template < typename... Ts>             void print_attribs( std::ostream & os, std::string const & name, char const * val, Ts&&... ts );
template < typename... Ts>             void print_attribs( std::ostream & os, std::string const & name, std::string const & val, Ts&&... ts );

void print_attribs( std::ostream & os ) { }

template < typename... Ts>
void print_attribs( std::ostream & os, char const * name, char const * val, Ts&&... ts ) { 
    os << " " << name << "=\"" << val << "\"";
    print_attribs( os, std::forward<Ts>(ts)... );
}

template < typename... Ts>
void print_attribs( std::ostream & os, std::string const & name, char const * val, Ts&&... ts ) { 
    print_attribs( os, name.c_str(), val, std::forward<Ts>(ts)... );
}

template < typename... Ts>
void print_attribs( std::ostream & os, char const * name, std::string const & val, Ts&&... ts ) { 
    os << " " << name << "=\"" << val << "\"";
    print_attribs( os, std::forward<Ts>(ts)... );
}

template < typename... Ts>
void print_attribs( std::ostream & os, std::string const & name, std::string const & val, Ts&&... ts ) { 
    print_attribs( os, name.c_str(), val, std::forward<Ts>(ts)... );
}

template < typename T, typename... Ts>
void print_attribs( std::ostream & os, char const * name, T&& val, Ts&&... ts ) { 
    os << " " << name << "=" << std::forward<T>(val);
    print_attribs( os, std::forward<Ts>(ts)... );
}

template < typename T, typename... Ts>
void print_attribs( std::ostream & os, std::string const & name, T&& val, Ts&&... ts ) { 
    print_attribs( os, name.c_str(), std::forward<T>(val), std::forward<Ts>(ts)... );
}

template < typename... Ts>
void print( std::ostream & os, char const * name, Ts&&... ts ) {
    static_assert( sizeof...(ts) % 2 == 0, "arguments must be paired of string and value" );
    os << "<parameter name=\"" << name << "\"";
    print_attribs( os, std::forward<Ts>(ts)... );
    os << " />";
}

template < typename... Ts>
void print( std::ostream & os, std::string const & name, Ts&&... ts ) {
    print( os, name.c_str(), std::forward<Ts>(ts)... );
}

int main() {
    auto endl = [] { std::cout << std::endl; };
    print( std::cout, "example", "foo", 10 ); endl();
    print( std::cout, "example", "foo", 10, "bar", "bare" ); endl();
    print( std::cout, "example", "foo", 10, "bar", 3.14f ); endl();
    print( std::cout, "example", "foo", 10, "bar", 3.14f, "bar", 3.14f ); endl();
    print( std::cout, "example", "foo", 10, "bar", "bare", "baz", 3.14f ); endl();
}
