#include <vector>
#include <utility>
#include <iterator>

namespace detail
{
    template <typename R>
        void do_concatenation(R& accum) {}

    template <typename R, typename First, typename... More> 
        void do_concatenation(R& accum, First const& first, More const&... more)
        {
            using std::begin;
            using std::end;
            std::copy(begin(first), end(first), std::inserter(accum, end(accum)));

            do_concatenation(accum, more...);
        }
}

template <typename Result, typename... Containters> 
   Result concatenate(Containters const&... containers)
{
    Result accum;
    detail::do_concatenation(accum, containers...);
    return accum;
}

template <typename First, typename... More> 
   std::vector<typename First::value_type> to_vector(First const& first, More const&... containers)
{
    return concatenate<std::vector<typename First::value_type>>(first, containers...);
}

/// demo
#include <set>
#include <list>
#include <iostream>

#include <map>
#include <string>

int main()
{
    auto x = to_vector(std::vector<int> { 1,2,3 }, std::list<int> { 9,8,11 }, std::set<int> { 42 });
    
    for (auto i : x)
       std::cout << i << " ";
    
    std::cout << std::endl;
       
    // fun with maps:
    auto y = concatenate<std::map<long, std::string> >(
            std::map<int,      const char*> { { 1, "one" }, { 2, "two" } },
            std::map<unsigned, std::string> { { 1, "one" }, { 3, "three" } }            
        );
        
    for (auto kvp : y)
       std::cout << "(" << kvp.first  << ", " << kvp.second << ")";
       
}
