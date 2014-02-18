#include <iostream>
#include <memory>
#include <cstring>
#include <boost/type_traits/add_const.hpp>
#include <boost/mpl/identity.hpp>

using namespace std;

template <template<typename> class F>
class Wrapper {
public:
    Wrapper(typename F<char>::type *buffer) : m_buffer(buffer) 
    { }
    
	typename F<char>::type * GetBuffer() 
    { 
        return m_buffer; 
    }
	
private:
	typename F<char>::type *m_buffer;
};

typedef Wrapper<boost::add_const> ConstWrapper;
typedef Wrapper<boost::mpl::identity> NonConstWrapper;

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