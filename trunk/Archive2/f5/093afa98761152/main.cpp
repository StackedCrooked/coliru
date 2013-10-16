#include <boost/multi_array.hpp>

typedef uint32_t object_identifier_t;
typedef std::pair<double, object_identifier_t> object_tab_t;
typedef boost::multi_array<object_tab_t, 2> index_t;

int main()
{
    index_t ix;
    assert( (ix[0].begin() -> second) == object_identifier_t(42) ); // <-- Error steams from here 
}
