#include <fstream>

class IO
{
        std::ifstream  m_ifs;  // due to this instance, IO is not copyable
};

// #define NEXT_LINE_CAUSES_CC_OF_IO

class Foo
{
#ifdef NEXT_LINE_CAUSES_CC_OF_IO
        IO  m_io;
#endif

public:
        static Foo NamedConstructor() {
                return Foo();
        }
private:
        Foo() { }
};

int
main( int argv, char* argc[] )
{
        Foo f = Foo::NamedConstructor();
}
