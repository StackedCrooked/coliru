#include <boost/variant/variant.hpp>

#include <memory>

int main()
{
   static_assert( !std::is_copy_constructible<boost::variant<std::unique_ptr<int>>>(), "Look at all this suck" );
}