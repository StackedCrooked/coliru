#include <iostream>

class A {
    std::string _str;
public:
    A( const char * str, size_t len ) : _str{str,len} {}
    friend std::ostream & operator<<( std::ostream & o, const A& a ) {
        return o << a._str;
    }
};
A operator"" _(const char* str, size_t len) { A a{str,len}; std::cout << str << " len=" << len << std::endl; return a; }

template <typename AT> class CharSeq {};

typedef CharSeq<decltype("catch"_)> CatchKeyword;

void w() {}

template<typename T, typename ... Etc> void w( T x, Etc... cetera ) {
    std::cout << ' ' << x;
    w(cetera...);
}

template<typename ... Etc> void write( Etc... cetera ) {
    w(cetera...);
    std::cout << std::endl;
}

int main()
{
      write( "catch"_, "this is longer %d"_, 5, 5.7 );
      return 0;
}

//Compile with -std=c++0x -fstring-template-arguments
