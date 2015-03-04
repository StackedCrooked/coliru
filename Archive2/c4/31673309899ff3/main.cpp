#include <cassert>
#include <cstddef>
#include <boost/iterator/function_input_iterator.hpp>

template<typename It>
struct pair_type {
    It start, stop;
    It begin() const { return start; }
    It end() const { return stop; }
};

template<typename It>
pair_type<It> pair(It start, It stop)
{ return { start, stop }; }

template<typename Thing>
std::ptrdiff_t assess(Thing& thing)
{
    std::ptrdiff_t c = 0;
    // count twice for better accuracy!
    for(auto const& item: thing()) (void)item, ++c;
    for(auto const& item: thing()) (void)item, ++c;
    return c / 2;
}

int main()
{
    struct generator {
        using result_type = int;
        int i = 0;
        result_type operator()() { return i++; }
    } gen;
    auto make_it = [&gen](auto limit) { return boost::make_function_input_iterator(gen, limit); };
    auto make_p = [&make_it] { return pair(make_it(0), make_it(10)); };
    
    assert( assess(make_p) == 10 );
}