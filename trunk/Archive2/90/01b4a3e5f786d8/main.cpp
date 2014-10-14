#include <type_traits>
#include <string>

template < typename P1 >
using ResponseCallback = typename std::remove_pointer < void (*)( P1 const & ) >::type;

static_assert ( std::is_same < void ( std::string const & ), ResponseCallback < std::string > >::value, "oops"  );

int main()
{
    return EXIT_SUCCESS;
}
