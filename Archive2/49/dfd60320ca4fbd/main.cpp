#include <iostream>
#include <tuple>
#include <utility>
#include <array>
#include <streambuf>
#include <fstream>

    namespace serialize {
      namespace details {
        template<class T>
        bool write( std::streambuf& buf, const T& val ) {
          static_assert( std::is_standard_layout<T>{}, "data is not standard layout" );
          auto bytes = sizeof(T);
          return buf.sputn(reinterpret_cast<const char*>(&val), bytes) == bytes;
        }
        template<class T>
        bool read( std::streambuf& buf, T& val ) {
          static_assert( std::is_standard_layout<T>{}, "data is not standard layout" );
          auto bytes = sizeof(T);
          return buf.sgetn(reinterpret_cast<char*>(&val), bytes) == bytes;
        }
      }
      template<class T>
      bool read( std::streambuf& buf, T& val ) {
        using details::read; // enable ADL
        return read(buf, val);
      }
      template<class T>
      bool write( std::streambuf& buf, T const& val ) {
        using details::write; // enable ADL
        return write(buf, val);
      }
    }
    
    namespace baz {
        struct foo {int x;};
        struct bar { bar():x(3) {} operator int()const{return x;} void setx(int s){x=s;} int y = 1; private: int x; };
        // adl based read/write overloads:
        bool write( std::streambuf& buf, bar const& b ) {
            bool worked = serialize::write( buf, (int)b );
            worked = serialize::write( buf, b.y ) && worked;
            return worked;
        }
        bool read( std::streambuf& buf, bar& b ) {
            int x;
            bool worked = serialize::read( buf, x );
            if (worked) b.setx(x);
            worked = serialize::read( buf, b.y ) && worked;
            return worked;
        }
    }
int main() {
    {
        std::fstream f("hello.txt");
        bool w = serialize::write( *f.rdbuf(), baz::foo{2} );
        w = serialize::write( *f.rdbuf(), baz::bar{} ) && w;
        std::cout << w << '\n';
    }
    std::fstream f("hello.txt");
    baz::foo f2{1};
    bool w = serialize::read( *f.rdbuf(), f2 );
    std::cout << w << '\n';
    std::cout << f2.x << '\n';
}