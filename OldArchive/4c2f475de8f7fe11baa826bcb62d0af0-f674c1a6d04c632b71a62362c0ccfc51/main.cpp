#include <set>
#include <type_traits>

int main()
{
    typedef std::set<int> set_type;
    typedef set_type::iterator iter;
    typedef set_type::const_iterator const_iter;
    
    static_assert(std::is_same<iter, const_iter>::value, "See?");
}
