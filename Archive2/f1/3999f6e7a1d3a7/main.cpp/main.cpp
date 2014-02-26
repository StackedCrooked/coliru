#include <boost/function_types/is_callable_builtin.hpp>

struct foo { void operator()() const; };

static_assert(boost::function_types::is_callable_builtin<foo>::value, "yeah, right");

int main() {}
