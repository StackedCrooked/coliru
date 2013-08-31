#define BOOST_RESULT_OF_USE_DECLTYPE

#include <functional>

#include <boost/phoenix/phoenix.hpp>

struct foo { int bar() { return 42; } };

int main()
{
    using namespace boost::phoenix;
    using namespace placeholders;
    
    auto const bar = std::mem_fn(&foo::bar);
    foo f;
    return bar(arg1)(f);
}