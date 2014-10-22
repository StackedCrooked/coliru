#include <boost/pool/pool.hpp>
#include <boost/pool/pool_alloc.hpp>
#include <boost/make_shared.hpp>

int main(int argc, char** argv)
{
  boost::allocate_shared<int>( boost::fast_pool_allocator<int>() );

  boost::allocate_shared<int>(boost::fast_pool_allocator<int>(), 5);
}