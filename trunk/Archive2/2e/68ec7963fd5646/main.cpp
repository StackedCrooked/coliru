#include <boost/variant.hpp>
class b_fwd;
typedef boost::variant<boost::recursive_wrapper<b_fwd> > a;
class c_fwd;
typedef boost::variant<boost::recursive_wrapper<c_fwd> > b;

struct b_fwd : b {
    using b::b;
};

typedef boost::variant<double, char *> c;

struct c_fwd : c {
    using c::c;
};

void f(const b &b_node) 
{
    a a_node(boost::variant<b>(b_node)); 
}

int main() 
{
}
