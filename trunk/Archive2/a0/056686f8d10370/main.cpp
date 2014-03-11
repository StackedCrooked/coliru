#include <iostream>
#include <string>

template < typename... Ts>             void print_attribs( std::ostream & os, std::string const & name, std::string const & val, Ts&&... ts );
template < typename T, typename... Ts> void print_attribs( std::ostream & os, std::string const & name, T&& val, Ts&&... ts );
template < typename... Ts>             void print( std::ostream & os, std::string const & name, Ts&&... ts );
template < typename... Ts>             void print_attribs( std::ostream & os, std::string const & name, char const * val, Ts&&... ts );

void print_attribs( std::ostream & os ) { }

template < typename... Ts>
void print_attribs( std::ostream & os, std::string const & name, char const * val, Ts&&... ts ) { 
    os << " " << name << "=\"" << val << "\"";
    print_attribs( os, std::forward<Ts>(ts)... );
}

template < typename... Ts>
void print_attribs( std::ostream & os, std::string const & name, std::string const & val, Ts&&... ts ) { 
    os << " " << name << "=\"" << val << "\"";
    print_attribs( os, std::forward<Ts>(ts)... );
}

template < typename T, typename... Ts>
void print_attribs( std::ostream & os, std::string const & name, T&& val, Ts&&... ts ) { 
    os << " " << name << "=" << std::forward<T>(val);
    print_attribs( os, std::forward<Ts>(ts)... );
}

template < typename... Ts>
void print( std::ostream & os, std::string const & name, Ts&&... ts ) {
    os << "<parameter name=\"" << name << "\"";
    print_attribs( os, std::forward<Ts>(ts)... );
    os << "/>";
}

int main() {
    auto endl = [] { std::cout << std::endl; };
    print( std::cout, "example", "foo", 10 ); endl();
    print( std::cout, "example", "foo", 10, "bar", "bare" ); endl();
    print( std::cout, "example", "foo", 10, "bar", 3.14f ); endl();
    print( std::cout, "example", "foo", 10, "bar", 3.14f, "bar", 3.14f ); endl();
    print( std::cout, "example", "foo", 10, "bar", "bare", "baz", 3.14f ); endl();
}
