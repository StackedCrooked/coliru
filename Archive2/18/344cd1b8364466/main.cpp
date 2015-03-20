#include <boost/asio/spawn.hpp>
#include <boost/function.hpp>
#include <type_traits>

using boost::asio::yield_context;

#if 1
    using func_type = boost::function<void (int,int)>;
#else
    using func_type = std::function<void (int,int)>;
#endif

using namespace std;

template <class Handler>
void foo (Handler h,
  enable_if_t<is_same<result_of_t<Handler (yield_context)>, void>::value>* = 0) 
{}

template <typename Handler>
void foo (Handler h,
  enable_if_t<is_same<result_of_t<Handler (func_type)>, void>::value>* = 0)
{}

int main ()
{
  foo ([] (func_type f) {});
}