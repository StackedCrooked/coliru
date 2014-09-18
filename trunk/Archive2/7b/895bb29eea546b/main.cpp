#include <vector>
#include <memory>
#include <utility>
#include <type_traits>
#include <iostream>
#include <cmath>

template<typename data_type>
struct Sequence 
{
    // Recurrence termination
    void initAlgos(){}

    // Merge two sequences
    template<typename... A>
    void initAlgos(std::shared_ptr<Sequence>&& seq, A&&... args)
    {
        //_effects.insert( _effects.end(), seq->_effects.begin(), seq->_effects.end() );
        std::cout << "shared ptr\n";

        initAlgos(args...);
    }

    // Create an effect using a function which works on vectors
    template< typename F, typename... A>
    auto initAlgos(F&& f, A&&... args)
    -> decltype( f(std::declval<std::vector<data_type>&>()), void() )
    {
        //_effects.emplace_back(Effect_p(new CustomVectorBenchmark<data_type>(f)));
        std::cout << "vector\n";

        initAlgos(args...);
    }

    // Create an effect using a function which works on single values
    template<typename F, typename... A>
    auto initAlgos(F&& f, A&&... args)
    -> typename std::enable_if< std::is_convertible<decltype(f(std::declval<const data_type&>())), data_type>::value, void>::type
    {
        //_effects.emplace_back(Effect_p(new CustomValueBenchmark<data_type>(f)));
        std::cout << "single-argument\n";

        initAlgos(args...);
    }

    //std::vector<Effect_p> _effects{};
};

int main()
{
    Sequence<double> s;
s.initAlgos([] (const double& x) {return std::sin(x); },
            [] (std::vector<double>& vec) { for(auto& elt : vec) elt *= 0.5; } );
}