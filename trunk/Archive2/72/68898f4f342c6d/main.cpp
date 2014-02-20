#include <iostream>
#include <memory>
#include <cstring>
#include <boost/type_traits/add_const.hpp>
#include <boost/mpl/identity.hpp>

using namespace std;

template <typename F>
class Wrapper {
public:
    Wrapper(F *buffer) : m_buffer(buffer) 
    { }
    
    F * GetBuffer() 
    { 
        return m_buffer; 
    }
	
private:
	F *m_buffer;
};

typedef Wrapper<const char> ConstWrapper;
typedef Wrapper<char> NonConstWrapper;

void output(const char *buffer) {
    cout << "const=" << buffer << endl;
}

void output(char *buffer) {
    cout << "nonconst=" << buffer << endl;
}

int main() 
{
    const char *foo = "foo";
    ConstWrapper cwrap(foo);
    output(cwrap.GetBuffer());

    char bar[] = "bar";    
    NonConstWrapper wrap(bar);
    output(wrap.GetBuffer());

	return 0;
}