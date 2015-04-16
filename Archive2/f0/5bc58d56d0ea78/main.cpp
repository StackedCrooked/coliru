#include <boost/typeof/typeof.hpp>

BOOST_AUTO(const& vref, 7);

#include <type_traits>

static_assert( std::is_same<int const&, decltype(vref)>{}, "" );

int main(){}