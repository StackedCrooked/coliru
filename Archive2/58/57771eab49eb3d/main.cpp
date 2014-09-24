#include <boost/uuid/uuid.hpp>

struct SomeType {};
SomeType myOtherFunction(int) { return SomeType(); }
void foo(SomeType, boost::uuids::uuid) {}

#include <boost/bind.hpp>
#include <boost/function.hpp>

int main()
{
    boost::function<void(int, boost::uuids::uuid)> composed;

    composed = boost::bind(foo, boost::bind(myOtherFunction, _1), _2);
}
