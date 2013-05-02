#include <vector>
#include <type_traits>

int main()
{
    std::vector<int const> v;
   // typedef std::vector<int>::value_type       t1;
   // typedef std::vector<int const>::value_type t2;
    
    //static_assert(!std::is_same<t1, t2>::value, "hmmm");
}