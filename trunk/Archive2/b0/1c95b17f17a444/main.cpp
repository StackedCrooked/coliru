#include <memory>
#include <type_traits>

namespace std
{
    template<typename T, typename... Args>
    unique_ptr<T> make_unique( Args&&... );
}

namespace check_unique
{
    template<typename... Args>
    void make_unique( Args&&... );
    
    using namespace std;
    
    struct has_make_unique : integral_constant<bool, !is_same<decltype(make_unique<shared_ptr<int>>(declval<shared_ptr<int>>())),void>::value> {};
}

int main()
{
    static_assert( check_unique::has_make_unique::value, "" );
}
